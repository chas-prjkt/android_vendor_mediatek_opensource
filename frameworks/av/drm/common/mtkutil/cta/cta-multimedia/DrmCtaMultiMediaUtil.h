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

#ifndef __DRM_CTA_MULTIMEDIA_UTIL_H__
#define __DRM_CTA_MULTIMEDIA_UTIL_H__

#include <utils/String8.h>
#include <stdio.h>

namespace android
{

#define FOURCC(c1, c2, c3, c4) \
    (c1 << 24 | c2 << 16 | c3 << 8 | c4)

class DrmCtaMultiMediaUtil {
private:

    DrmCtaMultiMediaUtil();

public:
    static uint64_t ntoh64(uint64_t x);
    static void MakeFourCCString(uint32_t x, char *s);
    static bool isCompatibleBrand(uint32_t fourcc);
    static ssize_t readAt(int fd, off64_t offset, void *data, size_t size);
    static bool isExistedInMultiMediaList(const String8& fileType);
public:

    static const int MULTI_MEDIA_LIST_CNT = 11;
    static const char* MULTI_MEDIA_LIST[MULTI_MEDIA_LIST_CNT];

};

}

#endif // __DRM_CTA_UTIL_H__
