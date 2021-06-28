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

#define LOG_NDEBUG 0
#define LOG_TAG "DrmMtkUtil/CipherFileUtil"
#include <utils/Log.h>

#include <CipherFileUtil.h>
#include <CryptoHelper.h>
#include <DrmDef.h>

#include <cutils/properties.h>

#include <utils/String8.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BLK_LEN 1024

using namespace android;

bool CipherFileUtil::sDebug = isEnableDebug();

bool CipherFileUtil::isEnableDebug() {
    char value[PROPERTY_VALUE_MAX];
    return property_get("vendor.debug.drm.logv", value, NULL) == 1;
}

int CipherFileUtil::CipherFileRead(int fd, void* buf, int byte_num, int offset,
                                   int data_offset, int data_size, CryptoHelper& hlp)
{
    if (fd < 0 || NULL == buf || byte_num < 0 || offset < 0 || data_offset < 0
            || data_size < 0 || (data_size % DrmDef::DRM_DCF_BLK_LENGTH) != 0)
    {
        ALOGE("CipherFileRead: error parameter: file_d[%d], buf[%p], byte_num[%d], offset[%d], data_offset[%d], data_size[%d]",
                fd, buf, byte_num, offset, data_offset, data_size);
        return -1;
    }
    if (sDebug) ALOGV("CipherFileRead: file_d[%d], buf[%p], byte_num[%d], offset[%d], data_offset[%d], data_size[%d]",
            fd, buf, byte_num, offset, data_offset, data_size);

    if (byte_num == 0)
    {
        ALOGW("CipherFileRead: byte_num = 0.");
        return 0;
    }

    if (offset > (data_size - DrmDef::DRM_DCF_IV_LENGTH)) // offset has been too much exceeded
    {
        ALOGW("CipherFileRead: too large offset [%d]", offset);
        return 0; // can read nothing
    }

    // calculate how many cipher blocks should be read and decrypted
    int blk_begin = offset / DrmDef::DRM_DCF_BLK_LENGTH;
    if (sDebug) ALOGV("CipherFileRead: start from block #[%d]", blk_begin);
    int delta_begin = offset - blk_begin * DrmDef::DRM_DCF_BLK_LENGTH; // in bytes
    if (sDebug) ALOGV("CipherFileRead: offset at the first block: [%d]", delta_begin);

    int blk_end = (offset + byte_num) / DrmDef::DRM_DCF_BLK_LENGTH;
    blk_end += 1;
    blk_end += (((offset + byte_num) % DrmDef::DRM_DCF_BLK_LENGTH) != 0) ? 1 : 0;

    bool final = false;
    if (blk_end > ((data_size - DrmDef::DRM_DCF_IV_LENGTH) / DrmDef::DRM_DCF_BLK_LENGTH))
    {
        final = true;
        blk_end = (data_size - DrmDef::DRM_DCF_IV_LENGTH) / DrmDef::DRM_DCF_BLK_LENGTH;
    }
    if (sDebug) ALOGV("CipherFileRead: end at block #[%d]", blk_end);
    if (sDebug) ALOGV("CipherFileRead: final block tag: [%d]", (int)final);

    // the total amount of bytes need to be read from original encrypted data
    int byte_cnt = (blk_end - blk_begin) * DrmDef::DRM_DCF_BLK_LENGTH;
    if (sDebug) ALOGV("CipherFileRead: [%d] bytes to be read", byte_cnt);

    // seek and read necessary bytes (iv & data)
    unsigned char iv[DrmDef::DRM_DCF_IV_LENGTH];
    bzero(iv, sizeof(iv));
    if (-1 == lseek(fd, data_offset + blk_begin * DrmDef::DRM_DCF_BLK_LENGTH, SEEK_SET))
    {
        ALOGE("CipherFileRead: failed to seek to [%d+%d*%d]!", data_offset, blk_begin, DrmDef::DRM_DCF_BLK_LENGTH);
        return -1;
    }
    if (DrmDef::DRM_DCF_IV_LENGTH != read(fd, iv, sizeof(iv)))
    {
        ALOGE("CipherFileRead: failed to read [%d] bytes iv data!", DrmDef::DRM_DCF_BLK_LENGTH);
        return -1;
    }

    unsigned char* temp = new unsigned char[byte_cnt];
    bzero(temp, (size_t)byte_cnt);
    if (-1 == lseek(fd, data_offset + DrmDef::DRM_DCF_IV_LENGTH + blk_begin * DrmDef::DRM_DCF_BLK_LENGTH, SEEK_SET))
    {
        ALOGE("CipherFileRead: failed to seek to [%d+%d+%d*%d]!", data_offset, DrmDef::DRM_DCF_IV_LENGTH,
            blk_begin, DrmDef::DRM_DCF_BLK_LENGTH);
        delete[] temp;
        return -1;
    }
    if (byte_cnt != read(fd, temp, (size_t)byte_cnt))
    {
        ALOGE("CipherFileRead: failed to read [%d] bytes data!", byte_cnt);
        delete[] temp;
        return -1;
    }

    // decryption operation
    int outSize = hlp.desiredOutBufSize(byte_cnt);
    unsigned char* out = new unsigned char[outSize];
    bzero(out, outSize);

    int length = 0;
    int ret = hlp.doCryption(temp, byte_cnt, out, length, iv, final);

    int bytesRead = -1;
    if (1 == ret) // decryption success
    {
        if (length > delta_begin)
        {
            if (sDebug) ALOGV("CipherFileRead: decryption and read sucess.");
            bytesRead = (byte_num < (length - delta_begin)) ? byte_num : (length - delta_begin);
            memcpy(buf, out + delta_begin, (size_t)bytesRead); // the {buf} should be large enough!!
        }
        else // no available data at specified offset
        {
            ALOGD("CipherFileRead: decryption sucess, but not enough data at specified offset.");
            bytesRead = 0;
        }
    }
    else
    {
        ALOGE("CipherFileRead: decryption failed.");
    }

    delete[] temp;
    delete[] out;
    return bytesRead;
}

// Add for Decode image with open decrypt seesion with ashmem
int CipherFileUtil::CipherFileRead(char* data, void* buf, int byte_num, int offset,
                                   int data_offset, int data_size, CryptoHelper& hlp)
{
    ALOGD("CipherFileRead: enter data[%p] data_offset[%d] data_size[%d]", data, data_offset, data_size);
    if (data == NULL || NULL == buf || byte_num < 0 || offset < 0 || data_offset < 0
            || data_size < 0 || (data_size % DrmDef::DRM_DCF_BLK_LENGTH) != 0)
    {
        ALOGE("CipherFileRead: error parameter: data[%p], buf[%p], byte_num[%d], offset[%d], data_offset[%d], data_size[%d]",
                data, buf, byte_num, offset, data_offset, data_size);
        return -1;
    }
    ALOGD("CipherFileRead: data[%p], buf[%p], byte_num[%d], offset[%d], data_offset[%d], data_size[%d]",
            data, buf, byte_num, offset, data_offset, data_size);

    if (byte_num == 0)
    {
        ALOGW("CipherFileRead: byte_num = 0.");
        return 0;
    }

    if (offset > (data_size - DrmDef::DRM_DCF_IV_LENGTH)) // offset has been too much exceeded
    {
        ALOGW("CipherFileRead: too large offset [%d]", offset);
        return 0; // can read nothing
    }

    char* curIndex = data;

    // calculate how many cipher blocks should be read and decrypted
    int blk_begin = offset / DrmDef::DRM_DCF_BLK_LENGTH;
    ALOGD("CipherFileRead: start from block #[%d]", blk_begin);
    int delta_begin = offset - blk_begin * DrmDef::DRM_DCF_BLK_LENGTH; // in bytes
    ALOGD("CipherFileRead: offset at the first block: [%d]", delta_begin);

    int blk_end = (offset + byte_num) / DrmDef::DRM_DCF_BLK_LENGTH;
    blk_end += 1;
    blk_end += (((offset + byte_num) % DrmDef::DRM_DCF_BLK_LENGTH) != 0) ? 1 : 0;

    bool final = false;
    if (blk_end > ((data_size - DrmDef::DRM_DCF_IV_LENGTH) / DrmDef::DRM_DCF_BLK_LENGTH))
    {
        final = true;
        blk_end = (data_size - DrmDef::DRM_DCF_IV_LENGTH) / DrmDef::DRM_DCF_BLK_LENGTH;
    }
    ALOGD("CipherFileRead: end at block #[%d]", blk_end);
    ALOGD("CipherFileRead: final block tag: [%d]", (int)final);

    // the total amount of bytes need to be read from original encrypted data
    int byte_cnt = (blk_end - blk_begin) * DrmDef::DRM_DCF_BLK_LENGTH;
    ALOGD("CipherFileRead: [%d] bytes to be read", byte_cnt);

    // seek and read necessary bytes (iv & data)
    unsigned char iv[DrmDef::DRM_DCF_IV_LENGTH];
    bzero(iv, sizeof(iv));

    curIndex += (data_offset + blk_begin * DrmDef::DRM_DCF_BLK_LENGTH);
    ALOGD("iv bytes: %x %x %x %x %x %x", curIndex[0], curIndex[1], curIndex[2], curIndex[3], curIndex[4], curIndex[5]);
    memcpy(iv, curIndex, sizeof(iv));
    curIndex += sizeof(iv);
    /*
    if (-1 == lseek(fd, data_offset + blk_begin * DrmDef::DRM_DCF_BLK_LENGTH, SEEK_SET))
    {
        ALOGE("CipherFileRead: failed to seek to [%d+%d*%d]!", data_offset, blk_begin, DrmDef::DRM_DCF_BLK_LENGTH);
        return -1;
    }
    if (DrmDef::DRM_DCF_IV_LENGTH != read(fd, iv, sizeof(iv)))
    {
        ALOGE("CipherFileRead: failed to read [%d] bytes iv data!", DrmDef::DRM_DCF_BLK_LENGTH);
        return -1;
    }*/

    unsigned char* temp = new unsigned char[byte_cnt];
    bzero(temp, (size_t)byte_cnt);

    curIndex = (data + data_offset + DrmDef::DRM_DCF_IV_LENGTH + blk_begin * DrmDef::DRM_DCF_BLK_LENGTH);

    ALOGD("CipherFileRead: curIndex [%p]", curIndex);
    if (curIndex > (data + data_offset + data_size) || (curIndex + byte_cnt) > (data + data_offset + data_size)) {
        ALOGD("CipherFileRead: error, out of data boundary, curIndex[%p] > %p, byte_cnt[%d]", curIndex,
              (data + data_offset + data_size), byte_cnt);
        delete[] temp;
        return -1;
    }
    memcpy(temp, curIndex, (size_t)byte_cnt);

    // decryption operation
    int outSize = hlp.desiredOutBufSize(byte_cnt);
    unsigned char* out = new unsigned char[outSize];
    bzero(out, outSize);

    int length = 0;
    int ret = hlp.doCryption(temp, byte_cnt, out, length, iv, final);

    int bytesRead = -1;
    if (1 == ret) // decryption success
    {
        if (length > delta_begin)
        {
            if (sDebug) ALOGV("CipherFileRead: decryption and read sucess.");
            bytesRead = (byte_num < (length - delta_begin)) ? byte_num : (length - delta_begin);
            memcpy(buf, out + delta_begin, (size_t)bytesRead); // the {buf} should be large enough!!
        }
        else // no available data at specified offset
        {
            ALOGD("CipherFileRead: decryption sucess, but not enough data at specified offset.");
            bytesRead = 0;
        }
    }
    else
    {
        ALOGE("CipherFileRead: decryption failed.");
    }

    delete[] temp;
    delete[] out;
    return bytesRead;
}

// deprecated
int CipherFileUtil::CipherFileDump(int fd __attribute__((unused)),
                                   int data_offset __attribute__((unused)),
                                   int data_size __attribute__((unused)),
                                   CryptoHelper& hlp __attribute__((unused)))
{
    return 0;
}

// deprecated
int CipherFileUtil::CipherFileDump(String8 file_name, int fd, int data_offset, int data_size, CryptoHelper& hlp)
{
    file_name.append(String8(".dump"));
    FILE* fp_dump = fopen(file_name.string(), "wb");
    if (NULL == fp_dump)
    {
        return -1;
    }
    fseek(fp_dump, 0, SEEK_SET);

    // read, decypt, and dump
    unsigned char data[BLK_LEN];
    memset(data, 0, sizeof(data));

    int bytesRead = 0;
    int offset = 0;
    do
    {
        memset(data, 0, sizeof(data));
        bytesRead = CipherFileRead(fd, data, BLK_LEN, offset, data_offset, data_size, hlp);

        // dump to file
        fwrite(data, sizeof(unsigned char), bytesRead, fp_dump);
        if (sDebug) ALOGV("dump: fwrite size[%d]", bytesRead);
        offset += bytesRead;
    }
    while (bytesRead >= 1024);

    fclose(fp_dump);

    return 0;
}

int CipherFileUtil::CipherFileInstall(FILE* origin, int data_offset, int data_size, FILE* out,
                                      CryptoHelper& hlp, unsigned char* iv)
{
    if (NULL == origin || NULL == out || NULL == iv || data_offset < 0 || data_size < 0)
    {
        ALOGE("CipherFileInstall: error parameter: origin[%p], out[%p], iv[%p], data_offset[%d], data_size[%d]",
                origin, out, iv, data_offset, data_size);
        return -1;
    }
    if (sDebug) ALOGV("CipherFileInstall: origin[%p], out[%p], iv[%p], data_offset[%d], data_size[%d]",
            origin, out, iv, data_offset, data_size);

    // copy the first iv
    unsigned char iv_arr[DrmDef::DRM_DCF_IV_LENGTH];
    bzero(iv_arr, sizeof(iv_arr));
    memcpy(iv_arr, iv, sizeof(iv_arr));

    // write the first iv to file
    size_t res = fwrite(iv_arr, sizeof(unsigned char), sizeof(iv_arr), out);
    if (res != DrmDef::DRM_DCF_IV_LENGTH)
    {
        ALOGE("CipherFileInstall: failed to write first iv to output file.");
        return -1;
    }

    if (-1 == fseek(origin, data_offset, SEEK_SET))
    {
        ALOGE("CipherFileInstall: failed to seek to the start of content!");
        return -1;
    }

    // input buffer
    unsigned char buf_in[BLK_LEN];
    bzero(buf_in, sizeof(buf_in));

    // output buffer for encryption
    int desired_len = hlp.desiredOutBufSize(BLK_LEN);
    unsigned char* buf_out = new unsigned char[desired_len];
    bzero(buf_out, (size_t)desired_len);

    // read, encrypt, and write to file
    size_t cnt = 0;
    size_t cnt_total = 0;
    int len_out = 0;
    while ((int)cnt_total < data_size)
    {
        bzero(buf_in, sizeof(buf_in));
        bzero(buf_out, (size_t)desired_len);

        cnt = fread(buf_in, sizeof(unsigned char),
                ((data_size - cnt_total) > BLK_LEN) ? BLK_LEN : (data_size - cnt_total), origin);
        cnt_total += cnt;

        if (1 != hlp.doCryption(buf_in, (int)cnt, buf_out, len_out, iv_arr, ((int)cnt_total >= data_size)))
        {
            ALOGE("CipherFileInstall: encryption operation failed.");
            goto ERROR;
        }

        // copy next iv
        memcpy(iv_arr, buf_out + len_out - DrmDef::DRM_DCF_IV_LENGTH, sizeof(iv_arr));

        // save to output file
        size_t result = fwrite(buf_out, sizeof(unsigned char), (size_t)len_out, out);
        if (result != (size_t)len_out)
        {
            ALOGE("CipherFileInstall: failed to write data to output file.");
            goto ERROR;
        }
    }

    delete[] buf_out;
    return 0;

ERROR:
    delete[] buf_out;
    return -1;
}
