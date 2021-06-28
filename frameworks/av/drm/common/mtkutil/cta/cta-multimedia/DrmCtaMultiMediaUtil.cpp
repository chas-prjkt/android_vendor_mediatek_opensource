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
#define LOG_TAG "DrmCtaMultiMediaUtil"
#include <utils/Log.h>

#include <DrmCtaMultiMediaUtil.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>


using namespace android;

const int DrmCtaMultiMediaUtil::MULTI_MEDIA_LIST_CNT;
const char* DrmCtaMultiMediaUtil::MULTI_MEDIA_LIST[MULTI_MEDIA_LIST_CNT] = {
    "video/mp4",
    "video/3gp",
    "video/3gpp",
    "video/quicktime",
    "video/x-flv",
    "video/avi",
    "video/x-ms-wmv",
    "video/asf",
    "audio/x-ms-wma",
    "audio/x-wav",
    "audio/flac"
};

uint64_t DrmCtaMultiMediaUtil::ntoh64(uint64_t x) {
    return ((uint64_t)ntohl(x & 0xffffffff) << 32) | ntohl(x >> 32);
}

void DrmCtaMultiMediaUtil::MakeFourCCString(uint32_t x, char *s) {
    s[0] = x >> 24;
    s[1] = (x >> 16) & 0xff;
    s[2] = (x >> 8) & 0xff;
    s[3] = x & 0xff;
    s[4] = '\0';
}

bool DrmCtaMultiMediaUtil::isCompatibleBrand(uint32_t fourcc) {
    static const uint32_t kCompatibleBrands[] = {
        FOURCC('i', 's', 'o', 'm'),
        FOURCC('i', 's', 'o', '2'),
        FOURCC('a', 'v', 'c', '1'),
        FOURCC('3', 'g', 'p', '4'),
        FOURCC('m', 'p', '4', '1'),
        FOURCC('m', 'p', '4', '2'),

        // Won't promise that the following file types can be played.
        // Just give these file types a chance.
        FOURCC('q', 't', ' ', ' '),  // Apple's QuickTime
        FOURCC('M', 'S', 'N', 'V'),  // Sony's PSP

        FOURCC('3', 'g', '2', 'a'),  // 3GPP2
        FOURCC('3', 'g', '2', 'b'),
    };

    for (size_t i = 0;
         i < sizeof(kCompatibleBrands) / sizeof(kCompatibleBrands[0]);
         ++i) {
        if (kCompatibleBrands[i] == fourcc) {
            return true;
        }
    }

    return false;
}

ssize_t DrmCtaMultiMediaUtil::readAt(int fd, off64_t offset, void *data, size_t size) {
    ssize_t bytes;

    if(offset != lseek64(fd, offset, SEEK_SET)) {
        ALOGE("[ERROR][CTA5]readAt - lseek fail, reason[%s]", strerror(errno));
        return 0;
    }

    if(-1 == (bytes = read(fd, data, size))) {
        ALOGE("[ERROR][CTA5]readAt - read fail, reason[%s]", strerror(errno));
        return 0;
    }

    return bytes;
}

bool DrmCtaMultiMediaUtil::isExistedInMultiMediaList(const String8& mime) {
    bool result = false;
    for(int i = 0; i < DrmCtaMultiMediaUtil::MULTI_MEDIA_LIST_CNT; i++)
    {
        ALOGD("isExistedInMultiMediaList: compare [%s] with [%s]",
            DrmCtaMultiMediaUtil::MULTI_MEDIA_LIST[i],
            mime.string());
        if(0 == strcmp(mime.string(), DrmCtaMultiMediaUtil::MULTI_MEDIA_LIST[i]))
        {
            ALOGD("isExistedInMultiMediaList: supported.");
            result = true;
            break;
        }
    }
    return result;
}
