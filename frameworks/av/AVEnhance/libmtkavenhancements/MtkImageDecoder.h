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

#ifndef MTK_IMAGE_DECODER_H_
#define MTK_IMAGE_DECODER_H_

#include <FrameDecoder.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/MediaCodec.h>
#include <media/stagefright/MediaSource.h>
#include <media/IMediaSource.h>
namespace android {

struct AMessage;
class MediaCodecBuffer;
class IMediaSource;
class VideoFrame;
struct MediaCodec;

struct MtkImageDecoder : public ImageDecoder {
    MtkImageDecoder(
            const AString &componentName,
            const sp<MetaData> &trackMeta,
            const sp<IMediaSource> &source);
protected:
    virtual ~MtkImageDecoder();
    virtual status_t extractInternal_ext() override;
    virtual sp<AMessage> onGetFormatAndSeekOptions(
            int64_t frameTimeUs,
            int seekMode,
            MediaSource::ReadOptions *options,
            sp<Surface> *window) override;

    virtual status_t onExtractRect(FrameRect *rect)override;

    virtual status_t onInputReceived(
            const sp<MediaCodecBuffer> &codecBuffer __unused,
            MetaDataBase &sampleMeta __unused,
            bool firstSample __unused,
            uint32_t *flags __unused)override { return OK; }

    virtual status_t onOutputReceived(
            const sp<MediaCodecBuffer> &videoFrameBuffer,
            const sp<AMessage> &outputFormat,
            int64_t timeUs,
            bool *done)override;
    virtual status_t init_ext(
            int64_t frameTimeUs, int option,
            int colorFormat ) override;
private:
    AString mComponentName;
    sp<MetaData> mTrackMeta;
    sp<IMediaSource> mSource;
    OMX_COLOR_FORMATTYPE mDstFormat;
    int32_t mDstBpp;
    std::vector<sp<IMemory> > mFrames;
    MediaSource::ReadOptions mReadOptions;
    sp<MediaCodec> mDecoder;
    sp<AMessage> mOutputFormat;
    bool mHaveMoreInputs;
    bool mFirstSample;
    bool mIsRGBReady;
    bool mIsAllDone;
    bool mIsStop;
    bool mIsEos;
    VideoFrame *mFrame;
    int32_t mWidth;
    int32_t mHeight;
    int32_t mGridRows;
    int32_t mGridCols;
    int32_t mInputCount;
    size_t mGridNum;
    int32_t mTileWidth;
    int32_t mTileHeight;
    int32_t mTilesDecoded;
    int32_t mTargetTiles;
    struct DecodeThread;
    sp<DecodeThread> mThread;
    sp<Surface> mSurface;

    bool receiveheifouputbuffer();

    DISALLOW_EVIL_CONSTRUCTORS(MtkImageDecoder);
};

}  // namespace android

#endif  // MTK_IMAGE_DECODER_H_
