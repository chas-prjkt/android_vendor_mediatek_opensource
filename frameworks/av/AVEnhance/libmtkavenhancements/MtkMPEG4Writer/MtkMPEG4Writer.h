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

#ifndef MTK_MPEG4_WRITER_H_

#define MTK_MPEG4_WRITER_H_

#include <stdio.h>

#include <media/IMediaSource.h>
#include <media/stagefright/MPEG4Writer.h>
#include <utils/List.h>
#include <utils/threads.h>
#include <media/stagefright/foundation/AHandlerReflector.h>
#include <media/stagefright/foundation/ALooper.h>

namespace android {

class MtkMPEG4Writer : public MPEG4Writer {
public:
    explicit MtkMPEG4Writer(int fd);

protected:
    virtual ~MtkMPEG4Writer();

    MtkMPEG4Writer(const MtkMPEG4Writer &);
    MtkMPEG4Writer &operator=(const MtkMPEG4Writer &);

public:
    // add common interfaces
    void        init();
    void        initStart(MetaData * /*param*/);
    // add notify file size to app for mms
    void        notifyEstimateSize(int64_t /*nTotalBytesEstimate*/);

    // for EIS
    void        setEISStop() { mIsEISStop = true; }
    bool        getEISStop() { return mIsEISStop; }
    void        setAudioTrackDurationUs(int64_t timeUs) { mAudioDurationUs = timeUs; };
    void        setVideoTrackDurationUs(int64_t timeUs) { mVideoDurationUs = timeUs; };
    int64_t     getAudioTrackDurationUs() { return mAudioDurationUs; };
    int64_t     getVideoTrackDurationUs() { return mVideoDurationUs; };
    int64_t     getEISStopWaitTime() { return mEISStopWaitTime; }

private:
    // add notify file size to app for mms
    uint32_t    mNotifyCounter;
    int32_t     mMediaInfoFlag;  // add for mtk defined infos in mediarecorder.h.

    // for EIS
    bool        mIsEISStop;
    int64_t     mAudioDurationUs;
    int64_t     mVideoDurationUs;
    int64_t     mEISStopWaitTime;
};

}  // namespace android

#endif  // MTK_MPEG4_WRITER_H_
