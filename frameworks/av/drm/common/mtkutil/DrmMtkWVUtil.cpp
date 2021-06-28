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
#define LOG_TAG "WV/DrmMtkWVUtil"
#include <utils/Log.h>

#include <drm/drm_framework_common.h>
#include <drm/DrmMtkWVUtil.h>

#include <ByteBuffer.h>
#include <CryptoHelper.h>
#include <DrmTypeDef.h>
#include <DrmUtil.h>

#include <utils/String8.h>

#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define AES128CBC_KEN_LEN 16
#define IV_LEN 16
#define KEYBOX_LEN 128

using namespace android;

const static String8 KB_LOCATION("/data/drm/");
const static String8 KB_DIR("/data/drm/wv/");
const static String8 KB_FILE("/data/drm/wv/kb.dat");



int DrmMtkWVUtil::loadKeybox(unsigned char* data, unsigned int offset, unsigned int length) {

    // open the kb data file
    FILE* fp = fopen(KB_FILE.string(), "rb");
    if (NULL == fp) {
        ALOGE("loadKeybox: failed to open kb data file, reason: [%s]", strerror(errno));
        return DRM_ERROR_UNKNOWN;
    }

    fseek(fp, 0, SEEK_SET);

    BYTE iv[IV_LEN];
    bzero(iv, sizeof(iv));
    if (IV_LEN != fread(iv, sizeof(BYTE), sizeof(iv), fp)) {
        ALOGE("loadKeybox: failed to read valid IV from kb data file, reason: [%s]", strerror(errno));
        fclose(fp);
        return DRM_ERROR_UNKNOWN;
    }

    BYTE data_in[KEYBOX_LEN + 16];
    bzero(data_in, sizeof(data_in));
    if ((KEYBOX_LEN + 16) != fread(data_in, sizeof(BYTE), sizeof(data_in), fp)) {
        ALOGE("loadKeybox: failed to read valid data from kb data file, reason: [%s]", strerror(errno));
        fclose(fp);
        return DRM_ERROR_UNKNOWN;
    }

    fclose(fp);

    ByteBuffer key(DrmUtil::getDrmKey());

    BYTE key_buf[AES128CBC_KEN_LEN];
    bzero(key_buf, sizeof(key_buf));
    memcpy(key_buf, key.buffer(), key.length());

    CryptoHelper hlp(CryptoHelper::CIPHER_AES128CBC, key_buf, 0);

    BYTE keybox[KEYBOX_LEN];
    bzero(keybox, sizeof(keybox));

    int out_len = 0;
    hlp.doCryption(data_in, sizeof(data_in), keybox, out_len, iv, true);

    int valid_cnt = ((int)(offset + length) <= out_len) ? length : (out_len - offset);
    valid_cnt = (valid_cnt < 0) ? 0 : valid_cnt;
    memcpy(data, keybox + offset, (size_t)valid_cnt);

    return DRM_NO_ERROR;
}

int DrmMtkWVUtil::saveKeybox(unsigned char* data, unsigned int length) {
    DrmUtil::checkDir(KB_DIR);
    FILE* fp = fopen(KB_FILE.string(), "wb");
    if (NULL == fp) {
        ALOGE("saveKeybox: failed to open kb data file for write, reason: [%s]", strerror(errno));
        return DRM_ERROR_UNKNOWN;
    }

    //chanage permission to avoid other and group users writing file
    int ret = chmod(KB_FILE.string(), 0644);
    if (ret != 0)
    {
        ALOGE("fchmod failed, reason: [%s]", strerror(errno));
    }

    fseek(fp, 0, SEEK_SET);

    ByteBuffer key(DrmUtil::getDrmKey());

    BYTE key_buf[AES128CBC_KEN_LEN];
    bzero(key_buf, sizeof(key_buf));
    memcpy(key_buf, key.buffer(), key.length());

    CryptoHelper hlp(CryptoHelper::CIPHER_AES128CBC, key_buf, 1);

    int out_size = hlp.desiredOutBufSize(length);
    BYTE* out = new BYTE[out_size];
    bzero(out, (size_t)out_size);

    String8 iv("4074BCC61602B5BE");
    int out_len = 0;
    hlp.doCryption(data, (int)length, out, out_len, (BYTE*)iv.string(), true);

    // write iv
    if (IV_LEN != fwrite(iv.string(), 1, iv.length(), fp)) {
        ALOGE("saveKeybox: failed to write IV to kb data file, reason: [%s]", strerror(errno));
        delete[] out;
        fclose(fp);
        return DRM_ERROR_UNKNOWN;
    }

    // write data
    if ((size_t)out_len != fwrite(out, sizeof(BYTE), (size_t)out_len, fp)) {
        ALOGE("saveKeybox: failed to write data to kb data file, reason: [%s]", strerror(errno));
        delete[] out;
        fclose(fp);
        return DRM_ERROR_UNKNOWN;
    }

    delete[] out;
    fclose(fp);
    return DRM_NO_ERROR;
}

String8 DrmMtkWVUtil::getDeviceId() {
    return DrmUtil::readId();
}
