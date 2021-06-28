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

#ifndef __DRM_MTK_WV_UTIL_H__
#define __DRM_MTK_WV_UTIL_H__

#include <utils/String8.h>

namespace android {

class DrmMtkWVUtil {
private:
    DrmMtkWVUtil();

public:
    static int loadKeybox(unsigned char* data, unsigned int offset, unsigned int length);
    static int saveKeybox(unsigned char* data, unsigned int length);
    static String8 getDeviceId();
};

}

#endif // __DRM_MTK_WV_UTIL_H__
