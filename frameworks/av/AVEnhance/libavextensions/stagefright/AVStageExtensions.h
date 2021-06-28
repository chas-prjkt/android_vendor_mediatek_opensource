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

#ifndef _AV_STAGE_EXTENSIONS_H_
#define _AV_STAGE_EXTENSIONS_H_

#include <common/CommonBase.h>
#include <utils/RefBase.h>

namespace android {

struct ACodec;
class MPEG4Writer;
struct ImageDecoder;
struct AString;
class MetaData;
class IMediaSource;
/*
 * package of vendor codes in libstagefright, mainly for objects creating.
 */

struct AVStageFactory {
    virtual sp<ACodec> createACodec();
    virtual sp<MPEG4Writer> createMPEG4Writer(int fd);
    virtual sp<ImageDecoder> createImageDecoder(
            const AString &componentName,
            const sp<MetaData> &trackMeta,
            const sp<IMediaSource> &source);
    FACTORY_INSTANCE_LOADER(AVStageFactory);
};


/*
 * package of vendor codes in libstagefright, mainly for utils or other.
 */

struct AVStageUtils {
    FACTORY_INSTANCE_LOADER(AVStageUtils);
};

}  // namespace android
#endif  // _AV_STAGE_EXTENSIONS_H_
