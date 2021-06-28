/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_NDEBUG 1
#define LOG_TAG "DrmMtkUtil/CryptoHelper"
#include <utils/Log.h>

#include <CryptoHelper.h>
#include <DrmTypeDef.h>

#include <openssl/evp.h>
#include <openssl/err.h>

#include <string.h>

using namespace android;

CryptoHelper::CryptoHelper(CIPHER cipher, BYTE* key, int is_enc) : m_key(NULL), m_isEnc(is_enc)
{
    EVP_CIPHER* evp_cipher = getCipher(cipher);
    EVP_CIPHER_CTX_init(&m_ctx);
    EVP_CipherInit_ex(&m_ctx, evp_cipher, NULL, NULL, NULL, is_enc);

    int keyLen = EVP_CIPHER_CTX_key_length(&m_ctx);
    m_key = new BYTE[keyLen];
    memcpy(m_key, key, keyLen); // should make sure those data in {key} buffer are enough.
}

CryptoHelper::~CryptoHelper()
{
    EVP_CIPHER_CTX_cleanup(&m_ctx);
    if (NULL != m_key)
    {
        delete[] m_key;
    }
}

int CryptoHelper::cipherKeyLen(CIPHER cipher)
{
    return getCipher(cipher)->key_len;
}

int CryptoHelper::cipherIvLen(CIPHER cipher)
{
    return getCipher(cipher)->iv_len;
}

int CryptoHelper::cipherBlkLen(CIPHER cipher)
{
    return getCipher(cipher)->block_size;
}

// return 1 for success with {len_out} bytes of data placed in {buf_out};
// return 0 for failure and no data result is available.
int CryptoHelper::doCryption(BYTE* buf_in, int len_in, BYTE* buf_out, int& len_out, BYTE* iv, bool is_final /* =false */)
{
    // if for RC4 cryption, IV may be NULL
    if (len_in <= 0 || buf_in == NULL || buf_out == NULL)
    {
        ALOGE("doCryption() : error parameter: len_in:[%d], buf_in:[%p], buf_out:[%p]",
                len_in, buf_in, buf_out);
        return 0;
    }
    ALOGV("doCryption() : len_in:[%d], buf_in:[%p], buf_out:[%p], is_final:[%d]",
            len_in, buf_in, buf_out, (int)is_final);

    // the iv is changed each time (AES128CBC), so we need to reinit cipher
    if (NULL != iv)
    {
        EVP_CipherInit_ex(&m_ctx, NULL, NULL, m_key, iv, m_isEnc);
    }

    BYTE* bp = buf_out;
    int length = 0;
    // call encryption / decryption operation
    if (!EVP_CipherUpdate(&m_ctx, bp, &length, buf_in, len_in))
    {
        ALOGE("doCryption() : error with [EVP_CipherUpdate]");
        goto Error;
    }
    len_out = length;
    ALOGV("doCryption() : [EVP_CipherUpdate] result length:[%d]", length);

    if (is_final) // if it is the final part of data, need to deal with "padding"
    {
        bp += length; // move the pointer
        length = 0;
        if (!EVP_CipherFinal_ex(&m_ctx, bp, &length))
        {
            ALOGE("doCryption() : error with [EVP_CipherFinal_ex]");
            goto Error;
        }
        len_out += length;
        ALOGV("doCryption() : [EVP_CipherFinal_ex] result length:[%d]", length);
    }

    ALOGV("doCryption() : return 1 for success");
    return 1;

Error:
    ALOGE("doCryption() : return 0 for failure");
    return 0;
}

int CryptoHelper::getKeyLen(void)
{
    return EVP_CIPHER_CTX_key_length(&m_ctx);
}

int CryptoHelper::getIvLen(void)
{
    return EVP_CIPHER_CTX_iv_length(&m_ctx);
}

int CryptoHelper::getBlkSize(void)
{
    return EVP_CIPHER_CTX_block_size(&m_ctx);
}

int CryptoHelper::desiredOutBufSize(int len_in)
{
    return calc_cipher_length(len_in);
}

// deprecated
int CryptoHelper::desiredInDataSize(int req_out_len)
{
    if (m_isEnc == 1) // for encryption, the original data is enough
    {
        return req_out_len;
    }
    else // for decryption, in order to get X bytes result, you should pass in
         // ((X / block_size + 1) * block_size) bytes of data.
    {
        int block_size = EVP_CIPHER_CTX_block_size(&m_ctx);
        return (req_out_len / block_size + 1) * block_size;
    }
}

int CryptoHelper::calc_cipher_length(int len_in)
{
    int block_size = EVP_CIPHER_CTX_block_size(&m_ctx);

    if (len_in < block_size) // not enough for 1 block
    {
        return block_size;
    }

    int block_cnt = len_in / block_size;
    int cipher_length = block_cnt * block_size;

    int block_final = len_in - cipher_length;
    if (block_final >= 0)
    {
        cipher_length += block_size;
    }

    return cipher_length;
}

EVP_CIPHER* CryptoHelper::getCipher(CIPHER cipher)
{
    switch (cipher)
    {
        case CIPHER_AES128CBC:
            return (EVP_CIPHER*)EVP_aes_128_cbc();
            break;
        case CIPHER_RC4:
            return (EVP_CIPHER*)EVP_rc4();
            break;
        default:
            break;
    }

    return NULL;
}
