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

//#define LOG_NDEBUG 0
#define LOG_TAG "MtkMPEG4Writer"

#include <algorithm>

#include <arpa/inet.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <utils/Log.h>

#include <functional>

#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/AUtils.h>
#include <media/stagefright/foundation/ColorUtils.h>
#include <media/stagefright/MediaBuffer.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MediaErrors.h>
#include <media/stagefright/Utils.h>
#include <media/mediarecorder.h>
#include <cutils/properties.h>

#include <media/stagefright/MetaDataBase.h>
#include "MtkMPEG4Writer.h"

namespace android {
#define TRACK_SKIPNOTIFY_RATIO          3

MtkMPEG4Writer::MtkMPEG4Writer(int fd)
    : MPEG4Writer(fd) {
    ALOGD("MtkMPEG4Writer constructor");
    // init will not been implemented when call initInternal() in MPEG4Writer constructor,
    // as MtkMPEG4Writer not been created yet, so init must been called again bellow.
    init();
}

MtkMPEG4Writer::~MtkMPEG4Writer() {
}

// add common interfaces
void MtkMPEG4Writer::init() {
    // add notify file size to app for mms
    mNotifyCounter = 0;
    mMediaInfoFlag = 0;  // add for mtk defined infos in mediarecorder.h.

    // for EIS
    mIsEISStop = false;
    mAudioDurationUs = 0;
    mVideoDurationUs = 0;
    mEISStopWaitTime = property_get_int64("mediarecord.eis.stopwaittime", 1000000LL);
    ALOGD("EIS stop waitting time = %lld", (long long)mEISStopWaitTime);
}

void MtkMPEG4Writer::initStart(MetaData *param) {
    // add for mtk defined infos in mediarecorder.h.
    int32_t mediainfoflag = 0;
    if (param &&
        param->findInt32(kKeyMediaInfoFlag, &mediainfoflag)) {
        mMediaInfoFlag = mediainfoflag;
    }
}

// add notify file size to app for mms
void MtkMPEG4Writer::notifyEstimateSize(int64_t nTotalBytesEstimate) {
    if (0 == (mNotifyCounter % TRACK_SKIPNOTIFY_RATIO)) {
        // add for mtk defined infos in mediarecorder.h.
        if (mMediaInfoFlag & RECORDING_SIZE_FLAG) {
            ALOGV("notify nTotalBytesEstimate %" PRId64 ", %d", nTotalBytesEstimate, mNotifyCounter);
            // add notify file size to app for mms
            notify(MEDIA_RECORDER_EVENT_INFO, MEDIA_RECORDER_INFO_RECORDING_SIZE, (int)nTotalBytesEstimate);
        }
    }
    mNotifyCounter++;
}


}  // namespace android
