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

#ifndef MTK_META_DATA_UTILS_H_

#define MTK_META_DATA_UTILS_H_

#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/MetaDataBase.h>

namespace android {

enum {
    kHEVCProfileMain                = 0x01,
    kHEVCProfileMain10              = 0x02,
    kHEVCProfileMainStillPicture    = 0x03,
};
bool MakeHEVCCodecSpecificData(MetaDataBase &meta, const uint8_t *data, size_t size);

}  // namespace android

#endif  // MTK_META_DATA_UTILS_H_
