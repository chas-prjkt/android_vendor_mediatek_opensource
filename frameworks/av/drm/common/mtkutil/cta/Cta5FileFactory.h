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

#ifndef __DRM_CTA5_FILE_FACTORY_H__
#define __DRM_CTA5_FILE_FACTORY_H__

#include <Cta5File.h>

namespace android
{
class Cta5FileFactory
{
public:
    /**
     * Create a Cta5NormalFile or Cta5MultimediaFile base on the fd
     */
    static Cta5File *createCta5File(int fd, String8 key);
    /**
     * Create a Cta5NormalFile or Cta5MultimediaFile base on the mime
     */
    static Cta5File *createCta5File(String8 mimeType,
                uint64_t datatLen, String8 key);
    static Cta5File *createCta5File(String8 mimeType,
                uint64_t datatLen, String8 key, bool isDcfFile);
    static bool isMultiMedia(int fd, const String8& key);
    static bool isMultiMedia(String8 mime);
};
}
#endif //__DRM_CTA5_FILE_FACTORY_H__
