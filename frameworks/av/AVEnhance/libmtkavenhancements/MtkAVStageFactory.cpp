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

#define LOG_TAG "MtkAVStageFactory"
#include <utils/Log.h>

#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/MediaDefs.h>
#include <media/DataSource.h>
#include <datasource/DataSourceFactory.h>
#include "MtkAVStageExtensions.h"

#include "MtkACodec/MtkACodec.h"
#include "MtkMPEG4Writer/MtkMPEG4Writer.h"

#include "MtkImageDecoder.h"
namespace android {

MtkAVStageFactory::MtkAVStageFactory() {}

MtkAVStageFactory::~MtkAVStageFactory() {}

extern "C" void* createVendorAVFactory() {
    return new MtkAVStageFactory;
}

sp<ACodec> MtkAVStageFactory::createACodec() {
    return new MtkACodec;
}

sp<MPEG4Writer> MtkAVStageFactory::createMPEG4Writer(int fd) {
    return new MtkMPEG4Writer(fd);
}

sp<ImageDecoder> MtkAVStageFactory::createImageDecoder(
        const AString &componentName,
        const sp<MetaData> &trackMeta,
        const sp<IMediaSource> &source) {
    return new MtkImageDecoder(componentName,trackMeta,source);
}

}  // namespace android
