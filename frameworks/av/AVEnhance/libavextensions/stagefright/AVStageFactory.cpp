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

#define LOG_TAG "AVStageFactory"
#include <utils/Log.h>

#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/ACodec.h>
#include <media/stagefright/MPEG4Writer.h>


#include "common/InstanceLoader.hpp"
#include "stagefright/AVStageExtensions.h"
#include <include/FrameDecoder.h>


namespace android {

AVStageFactory::AVStageFactory() {
}

AVStageFactory::~AVStageFactory() {
}

sp<ACodec> AVStageFactory::createACodec() {
    return new ACodec;
}
sp<MPEG4Writer> AVStageFactory::createMPEG4Writer(int fd) {
    return new MPEG4Writer(fd);
}

sp<ImageDecoder> AVStageFactory::createImageDecoder(const AString &componentName,
    const sp<MetaData> &trackMeta, const sp<IMediaSource> &source) {
    return new ImageDecoder(componentName, trackMeta, source);
}

// static
AVStageFactory *AVStageFactory::sInst =
        InstanceLoader<AVStageFactory>::createInstance("createVendorAVFactory");

}  // namespace android
