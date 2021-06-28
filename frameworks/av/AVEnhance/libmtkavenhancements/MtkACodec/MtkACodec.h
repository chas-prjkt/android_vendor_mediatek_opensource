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

#ifndef MTK_A_CODEC_H_
#define MTK_A_CODEC_H_

#include <media/stagefright/ACodec.h>

#include "roi/MtkRoi.h"

namespace android {

struct MtkACodec : public ACodec {
    MtkACodec();

protected:
    virtual ~MtkACodec();

    virtual status_t setupAudioCodec(
         status_t err, const char *mime, bool encoder, const sp<AMessage> &msg);

    virtual status_t setMtkParameters(const sp<IOMXNode> & omxNode,
            const sp<AMessage> & params, bool isEncoder);

    virtual status_t setAVSyncTime(const char* componentName,
            const sp<AMessage> bufferMeta,
            const sp<IOMXNode> & omxNode,
            const sp<AMessage> & msg);

private:
    int64_t mAnchorTimeRealUs;
    sp<IOMXNode> mOMXNode;

    status_t setAVSyncTime(const sp<IOMXNode> & omxNode, int64_t time);
    // for MTK_WMA_PLAYBACK_SUPPORT
    status_t setupWMACodec(bool encoder, int32_t numChannels, int32_t sampleRate);

    // #ifdef MTK_AUDIO_ADPCM_SUPPORT
    status_t setupADPCMCodec(const char *mime, const sp<AMessage> &msg);
    // #endif
    // #ifdef MTK_AUDIO_ALAC_SUPPORT
    status_t setupAlacCodec(const char *mime, const sp<AMessage> &msg);
    // #endif

    //#ifdef MTK_AUDIO_APE_SUPPORT
    status_t setupApeCodec(const char *mime, const sp<AMessage> &msg);
    // #endif

    //for mp3 lowpower
    virtual status_t setOmxReadMultiFrame(const sp<IOMXNode> &omxNode,
                const sp<AMessage> &msg);

    status_t getPortFormat(OMX_U32 portIndex, sp<AMessage> &notify);

    // get vendor extension parameters supported by the codec for a specific port and add it to
    // |format|
    status_t getVendorParameters(OMX_U32 portIndex, sp<AMessage> &format);

    status_t setupRawAudioFormat(
            OMX_U32 portIndex, int32_t sampleRate, int32_t numChannels,
            AudioEncoding encoding = kAudioEncodingPcm16bit);

private:

    enum {
        kPortIndexInput  = 0,
        kPortIndexOutput = 1
    };

    enum {
        kExtensionsUnchecked,
        kExtensionsNone,
        kExtensionsExist,
    } mVendorExtensionsStatus;

    //for ViLTE
    virtual status_t setViLTEParameters(const sp<IOMXNode> &omxNode, const sp<AMessage> &msg, bool fgCheckResolutionChange);

    //  for ThumbnailMode
    virtual status_t setThumbnailMode(const char* componentName,
        const sp<IOMXNode>&omxNode,
        const sp<AMessage> &msg,
        bool IsEncoder);

    // for ROI
    sp<MtkRoi> mRoi;

    DISALLOW_EVIL_CONSTRUCTORS(MtkACodec);
};

}  // namespace android

#endif  // MTK_A_CODEC_H_
