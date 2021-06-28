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

#define LOG_NDEBUG 0
#define LOG_TAG "APEExtractor"
#define MTK_LOG_ENABLE 1
#include <utils/Log.h>
#include "ID3.h"

#include <android/binder_ibinder.h> // for AIBinder_getCallingUid
#include <media/MediaExtractorPluginApi.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/MediaBufferGroup.h>
#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MediaErrors.h>
#include <media/stagefright/Utils.h>
#include <private/android_filesystem_config.h> // for AID_MEDIA
#include <utils/String8.h>

#include "stagefright/MediaDefs_MTK.h"
#include "APEExtractor.h"
#include "APETag.h"

namespace android
{

static inline bool shouldPlayPCMFloat(int bitsPerSample)
{
    return bitsPerSample > 16 && AIBinder_getCallingUid() == AID_MEDIA;
}

///#ifndef ANDROID_DEFAULT_CODE
// Everything must match except for
// protection, bitrate, padding, private bits, mode extension,
// copyright bit, original bit and emphasis.
// Yes ... there are things that must indeed match...
//static const uint32_t kMask = 0xfffe0c00;//0xfffe0cc0 add by zhihui zhang no consider channel mode

static bool getAPEInfo(
    DataSourceHelper *source, off_t *inout_pos, ape_parser_ctx_t *ape_ctx, bool parseall)
{
    unsigned int i;
    unsigned int file_offset = 0;
    bool ret = false;
    off_t ori_pos = *inout_pos;
    ///LOGD("getAPEInfo %d, %d", *inout_pos, parseall);
    memset(ape_ctx, 0, sizeof(ape_parser_ctx_t));
    char *pFile = new char[20480 + 1024];

    if (pFile == NULL)
    {
        ALOGE("getAPEInfo memory error");
        goto GetApeInfo_Exit;
    }

    if (source->readAt(*inout_pos, pFile, 20480 + 1024) <= 0)
    {
        goto GetApeInfo_Exit;
    }

    while (1)
    {
        char *sync;
        ///if (4 != fread(sync, 1, 4, fp))
        ///if((source->readAt(*inout_pos, sync, 4)!= 4)
        sync = pFile + (*inout_pos - ori_pos) ;

        if (*inout_pos - ori_pos > 20480)
        {
            ALOGE("getAPEInfo not ape %lld", (long long)*inout_pos);
            goto GetApeInfo_Exit;
        }

        if (memcmp(sync, "MAC ", 4) == 0)
        {
            ALOGV("getAPEInfo parse ok, %lx!!!!", *inout_pos);
            ///return false;
            break;
        }
        else if (memcmp(sync + 1, "MAC", 3) == 0)
        {
            *inout_pos += 1;
        }
        else if (memcmp(sync + 2, "MA", 2) == 0)
        {
            *inout_pos += 2;
        }
        else if (memcmp(sync + 3, "M", 1) == 0)
        {
            *inout_pos += 3;
        }
        else if ((memcmp("ID3", sync, 3) == 0))
        {
            size_t len =
                ((sync[6] & 0x7f) << 21)
                | ((sync[7] & 0x7f) << 14)
                | ((sync[8] & 0x7f) << 7)
                | (sync[9] & 0x7f);

            len += 10;

            ALOGV("getAPEInfo id3 tag %lld, len %zx", (long long)*inout_pos, len);
            *inout_pos += len;

            ori_pos = *inout_pos;

            if (source->readAt(*inout_pos, pFile, 20480 + 1024) <= 0)
            {
                goto GetApeInfo_Exit;
            }
        }
        else
        {
            *inout_pos += 4;
        }

    }

    file_offset = *inout_pos;
    memcpy(ape_ctx->magic, "MAC ", 4);
    ape_ctx->junklength = *inout_pos;
    *inout_pos += 4;

    //unsigned char sync4[4];
    //unsigned char sync2[2];

    if (source->readAt(*inout_pos, &ape_ctx->fileversion, sizeof(ape_ctx->fileversion)) < 0)
    {
        goto GetApeInfo_Exit;
    }

    if((ape_ctx->fileversion > 4200)
        || (ape_ctx->fileversion < 3940) )
    {
        ALOGV("getAPEInfo version is not match %d", ape_ctx->fileversion);
        goto GetApeInfo_Exit;
    }

    if (parseall == false)
    {
        ret = true;
        goto GetApeInfo_Exit;
    }

    *inout_pos += 2;

    if (ape_ctx->fileversion >= 3980)
    {
        if (source->readAt(*inout_pos, &ape_ctx->padding1, sizeof(ape_ctx->padding1)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->descriptorlength, sizeof(ape_ctx->descriptorlength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->headerlength, sizeof(ape_ctx->headerlength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->seektablelength, sizeof(ape_ctx->seektablelength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->wavheaderlength, sizeof(ape_ctx->wavheaderlength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->audiodatalength, sizeof(ape_ctx->audiodatalength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->audiodatalength_high, sizeof(ape_ctx->audiodatalength_high)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->wavtaillength, sizeof(ape_ctx->wavtaillength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->md5, 16) != 16)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 16;

        /* Skip any unknown bytes at the end of the descriptor.  This is for future  compatibility */
        if (ape_ctx->descriptorlength > 52)
        {
            *inout_pos += (ape_ctx->descriptorlength - 52);
        }

        /* Read header data */
        if (source->readAt(*inout_pos, &ape_ctx->compressiontype, sizeof(ape_ctx->compressiontype)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        if (ape_ctx->compressiontype > APE_MAX_COMPRESS)
        {
            ALOGE("getAPEInfo(Line%d): unsupported compressiontype = %u", __LINE__, ape_ctx->compressiontype);
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->formatflags, sizeof(ape_ctx->formatflags)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->blocksperframe, sizeof(ape_ctx->blocksperframe)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->finalframeblocks, sizeof(ape_ctx->finalframeblocks)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->totalframes, sizeof(ape_ctx->totalframes)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->bps, sizeof(ape_ctx->bps)) < 0)
        {
            goto GetApeInfo_Exit;
        }
        ALOGD("support 24bit, bps:%d",ape_ctx->bps);

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->channels, sizeof(ape_ctx->channels)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->samplerate, sizeof(ape_ctx->samplerate)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        if (ape_ctx->blocksperframe <= 0
                || ape_ctx->totalframes <= 0
                || ape_ctx->bps <= 0
                || ape_ctx->seektablelength <= 0
                || ape_ctx->samplerate <= 0
                || ape_ctx->samplerate > 192000)
        {
            ALOGD("getAPEInfo header error: blocksperframe %x,totalframes %x, bps %x,seektablelength %x, samplerate %x ",
                 ape_ctx->blocksperframe,
                 ape_ctx->totalframes,
                 ape_ctx->bps,
                 ape_ctx->seektablelength,
                 ape_ctx->samplerate);
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;
    }
    else
    {
        ape_ctx->descriptorlength = 0;
        ape_ctx->headerlength = 32;

        if (source->readAt(*inout_pos, &ape_ctx->compressiontype, sizeof(ape_ctx->compressiontype)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        if (ape_ctx->compressiontype > APE_MAX_COMPRESS)
        {
            ALOGE("getAPEInfo(Line%d): unsupported compressiontype = %u", __LINE__, ape_ctx->compressiontype);
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->formatflags, sizeof(ape_ctx->formatflags)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->channels, sizeof(ape_ctx->channels)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 2;

        if (source->readAt(*inout_pos, &ape_ctx->samplerate, sizeof(ape_ctx->samplerate)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->wavheaderlength, sizeof(ape_ctx->wavheaderlength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->wavtaillength, sizeof(ape_ctx->wavtaillength)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->totalframes, sizeof(ape_ctx->totalframes)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (source->readAt(*inout_pos, &ape_ctx->finalframeblocks, sizeof(ape_ctx->finalframeblocks)) < 0)
        {
            goto GetApeInfo_Exit;
        }

        *inout_pos += 4;

        if (ape_ctx->formatflags & MAC_FORMAT_FLAG_HAS_PEAK_LEVEL)
        {
            ///fseek(fp, 4, SEEK_CUR);
            *inout_pos += 4;
            ape_ctx->headerlength += 4;
        }

        if (ape_ctx->formatflags & MAC_FORMAT_FLAG_HAS_SEEK_ELEMENTS)
        {
            if (source->readAt(*inout_pos, &ape_ctx->seektablelength, sizeof(ape_ctx->seektablelength)) < 0)
            {
                goto GetApeInfo_Exit;
            }

            *inout_pos += 4;
            ape_ctx->headerlength += 4;
            ape_ctx->seektablelength *= sizeof(ape_parser_int32_t);
        }
        else
        {
            ape_ctx->seektablelength = ape_ctx->totalframes * sizeof(ape_parser_int32_t);
        }

        if (ape_ctx->formatflags & MAC_FORMAT_FLAG_8_BIT)
        {
            ape_ctx->bps = 8;
        }
        else if (ape_ctx->formatflags & MAC_FORMAT_FLAG_24_BIT)
        {
            ape_ctx->bps = 24;
            goto GetApeInfo_Exit;
        }
        else
        {
            ape_ctx->bps = 16;
        }

        if (ape_ctx->fileversion >= APE_MIN_VERSION)
        {
            ape_ctx->blocksperframe = 73728 * 4;
        }
        else if ((ape_ctx->fileversion >= 3900) || (ape_ctx->fileversion >= 3800 && ape_ctx->compressiontype >= APE_MAX_COMPRESS))
        {
            ape_ctx->blocksperframe = 73728;
        }
        else
        {
            ape_ctx->blocksperframe = 9216;
        }

        /* Skip any stored wav header */
        if (!(ape_ctx->formatflags & MAC_FORMAT_FLAG_CREATE_WAV_HEADER))
        {
            *inout_pos += ape_ctx->wavheaderlength;
        }

        if (ape_ctx->blocksperframe <= 0
                || ape_ctx->totalframes <= 0
                || ape_ctx->bps <= 0
                || ape_ctx->seektablelength <= 0
                || ape_ctx->samplerate <= 0
                || ape_ctx->samplerate > 192000)
        {
            ALOGD("getAPEInfo header error: blocksperframe %x,totalframes %x, bps %x,seektablelength %x, samplerate %x ",
                 ape_ctx->blocksperframe,
                 ape_ctx->totalframes,
                 ape_ctx->bps,
                 ape_ctx->seektablelength,
                 ape_ctx->samplerate);
            goto GetApeInfo_Exit;
        }
    }
    ape_ctx->totalsamples = ape_ctx->finalframeblocks;

    if (ape_ctx->totalframes > 1)
    {
        ape_ctx->totalsamples += ape_ctx->blocksperframe * (ape_ctx->totalframes - 1);
    }

    if (ape_ctx->seektablelength > 0)
    {
        ape_parser_uint32_t seekaddr = 0;
        ape_ctx->seektable = (uint32_t *)malloc(ape_ctx->seektablelength);

        if (ape_ctx->seektable == NULL)
        {
            goto GetApeInfo_Exit;
        }

        for (i = 0; i < ape_ctx->seektablelength / sizeof(ape_parser_uint32_t); i++)
        {
            if (source->readAt(*inout_pos, &seekaddr, 4) < 0)
            {
                free(ape_ctx->seektable);
                ape_ctx->seektable = NULL;
                goto GetApeInfo_Exit;
            }

            ape_ctx->seektable[i] = (seekaddr + file_offset);
            *inout_pos += 4;
        }
    }

    ape_ctx->firstframe = ape_ctx->junklength + ape_ctx->descriptorlength +
                          ape_ctx->headerlength + ape_ctx->seektablelength +
                          ape_ctx->wavheaderlength;
    ape_ctx->seektablefilepos = ape_ctx->junklength + ape_ctx->descriptorlength +
                                ape_ctx->headerlength;


    *inout_pos = ape_ctx->firstframe;

    ALOGV("getAPEInfo header info: offset %d, ape_ctx->junklength %x,ape_ctx->firstframe %x, ape_ctx->totalsamples %x,ape_ctx->fileversion %x, ape_ctx->padding1 %x ",
         file_offset,
         ape_ctx->junklength,
         ape_ctx->firstframe,
         ape_ctx->totalsamples,
         ape_ctx->fileversion,
         ape_ctx->padding1);

    ALOGV("ape_ctx->descriptorlength %x,ape_ctx->headerlength %x,ape_ctx->seektablelength %x,ape_ctx->wavheaderlength %x,ape_ctx->audiodatalength %x ",
         ape_ctx->descriptorlength,
         ape_ctx->headerlength,
         ape_ctx->seektablelength,
         ape_ctx->wavheaderlength,
         ape_ctx->audiodatalength);


    ALOGV("ape_ctx->audiodatalength_high %x,ape_ctx->wavtaillength %x,ape_ctx->compressiontype %x, ape_ctx->formatflags %x,ape_ctx->blocksperframe %x",
         ape_ctx->audiodatalength_high,
         ape_ctx->wavtaillength,
         ape_ctx->compressiontype,
         ape_ctx->formatflags,
         ape_ctx->blocksperframe);

    ALOGV("ape_ctx->finalframeblocks %x,ape_ctx->totalframes %x,ape_ctx->bps %x,ape_ctx->channels %x,ape_ctx->samplerate %x",
         ape_ctx->finalframeblocks,
         ape_ctx->totalframes,
         ape_ctx->bps,
         ape_ctx->channels,
         ape_ctx->samplerate);

    ret = true;

GetApeInfo_Exit:

    if (pFile)
    {
        delete[] pFile;
    }

    pFile = NULL;
    return ret;

}

class APESource : public MediaTrackHelper
{
public:
    APESource(
        AMediaFormat *meta, DataSourceHelper *source,
        off_t first_frame_pos, uint32_t totalsample, uint32_t finalsample,
        int32_t TotalFrame, uint32_t  *table_of_contents, int sample_per_frame,
        int32_t frm_size, int32_t pst_bound,uint32_t *sk_newframe,uint32_t *sk_seekbyte,
        bool useFloatPCM
    );
    int ape_calc_seekpos_by_microsecond(struct ape_parser_ctx_t *ape_ctx,
                                        int64_t millisecond,
                                        uint32_t *newframe,
                                        uint32_t *filepos,
                                        uint32_t *firstbyte,
                                        uint32_t *blocks_to_skip);
    virtual media_status_t start();
    virtual media_status_t stop();

    virtual media_status_t getFormat(AMediaFormat *);
    virtual media_status_t read(
        MediaBufferHelper **buffer, const ReadOptions *options = NULL);

protected:
    virtual ~APESource();

private:
    AMediaFormat *mMeta;
    DataSourceHelper *mDataSource;

    off_t mFirstFramePos;
    int32_t mTotalFrame;
    uint32_t mTotalsample;
    uint32_t mFinalsample;
    uint32_t *mTableOfContents;
    off_t mCurrentPos;
    int64_t mCurrentTimeUs;
    bool mStarted;
    int mSamplesPerFrame;
    int32_t mSt_bound;
    int mSampleRate;
    uint32_t *mNewframe;
    uint32_t *mSeekbyte;
    off_t mFileoffset;
    int64_t mCurrentFrame;
    MediaBufferGroup *mGroup;
    size_t kMaxFrameSize;
    bool mUseFloatPCM;

    APESource(const APESource &);
    APESource &operator=(const APESource &);
};

APESource::APESource(
    AMediaFormat *meta, DataSourceHelper *source,
    off_t first_frame_pos, uint32_t totalsample, uint32_t finalsample,
    int32_t TotalFrame, uint32_t  *table_of_contents, int sample_per_frame,
    int32_t frm_size, int32_t pst_bound,uint32_t *sk_newframe,uint32_t *sk_seekbyte,
    bool useFloatPCM
)
    : mMeta(meta),
      mDataSource(source),
      mFirstFramePos(first_frame_pos),
      mTotalFrame(TotalFrame),
      mTotalsample(totalsample),
      mFinalsample(finalsample),
      mTableOfContents(table_of_contents),
      mCurrentTimeUs(0),
      mStarted(false),
      mSamplesPerFrame(sample_per_frame),
      mSt_bound(pst_bound),
      mNewframe(sk_newframe),
      mSeekbyte(sk_seekbyte),
      mGroup(NULL),
      mUseFloatPCM(useFloatPCM)
{

    ALOGV("APESource %d, %lld, %d, %d, %d", mTotalsample, (long long)mFirstFramePos, mFinalsample, sample_per_frame, frm_size);
    mCurrentFrame = 0;
    mCurrentPos = 0;
    kMaxFrameSize = frm_size;
    mFileoffset = 0;
    mSampleRate = 0;
}


APESource::~APESource()
{
    if (mStarted)
    {
        stop();
    }
}

media_status_t APESource::start()
{
    CHECK(!mStarted);
    ALOGD("APESource::start In");

    mBufferGroup->add_buffer(kMaxFrameSize);

    mCurrentPos = mFirstFramePos;
    mCurrentTimeUs = 0;

    mStarted = true;
    off64_t fileoffset = 0;
    mDataSource->getSize(&fileoffset);

//    if (fileoffset < mTableOfContents[mTotalFrame - 1])
    if (fileoffset < mTableOfContents[mSt_bound- 1])
    {
        int i = 0;

//        for (i = 0; i < mTotalFrame; i++)
        for (i = 0; i < mSt_bound; i++)
        {
            if (fileoffset < mTableOfContents[i])
            {
                i--;
                break;
            }
            else if (fileoffset == mTableOfContents[i])
            {
                break;
            }
        }

        mFileoffset = mTableOfContents[i];
        ALOGD("mFileoffset redefine old %lld, new %lld", (long long)fileoffset, (long long)mFileoffset);
    }

    return AMEDIA_OK;
}

media_status_t APESource::stop()
{
    ALOGV("APESource::stop() In");
    CHECK(mStarted);

    if (mTableOfContents)
    {
        free(mTableOfContents);
    }

    mTableOfContents = NULL;
    mStarted = false;
    ALOGV("APESource::stop() out");
    return AMEDIA_OK;
}

media_status_t APESource::getFormat(AMediaFormat *meta) {
    ALOGV("APESource::getFormat");
    const media_status_t status = AMediaFormat_copy(meta, mMeta);
    if (status == OK && mUseFloatPCM) {
        AMediaFormat_setInt32(meta, AMEDIAFORMAT_KEY_PCM_ENCODING, kAudioEncodingPcmFloat);
    }
    return status;
}


int APESource:: ape_calc_seekpos_by_microsecond(struct ape_parser_ctx_t *ape_ctx,
        int64_t microsecond,
        uint32_t *newframe,
        uint32_t *filepos,
        uint32_t *firstbyte,
        uint32_t *blocks_to_skip)
{
    uint32_t n = 0xffffffff, delta;
    int64_t new_blocks;

    new_blocks = (int64_t)microsecond * (int64_t)ape_ctx->samplerate;
    new_blocks /= 1000000;

    if (ape_ctx->blocksperframe >= 0)
    {
        n = new_blocks / ape_ctx->blocksperframe;
    }

    if (n >= ape_ctx->totalframes)
    {
        return -1;
    }

    *newframe = n;
    *filepos = ape_ctx->seektable[n];
    *blocks_to_skip = new_blocks - (n * ape_ctx->blocksperframe);

    delta = (*filepos - ape_ctx->firstframe) & 3;
    ALOGV("ape_calc_seekpos_by_microsecond %d, %x, %x, %d", n, ape_ctx->seektable[n], ape_ctx->firstframe, delta);
    *firstbyte = 3 - delta;
    *filepos -= delta;

    return 0;
}

media_status_t APESource::read(
    MediaBufferHelper **out, const ReadOptions *options)
{
    *out = NULL;
    uint32_t newframe = 0 , firstbyte = 0;

    ///LOGV("APESource::read");
    int64_t seekTimeUs;
    ReadOptions::SeekMode mode;
    int32_t bitrate = 0;

    if (!AMediaFormat_getInt32(mMeta, AMEDIAFORMAT_KEY_BIT_RATE, &bitrate)
            || !AMediaFormat_getInt32(mMeta, AMEDIAFORMAT_KEY_SAMPLE_RATE, &mSampleRate))
    {
        ALOGI("no bitrate");
        return AMEDIA_ERROR_UNSUPPORTED;
    }

    if (options != NULL && options->getSeekTo(&seekTimeUs, &mode))
    {

        {

            int64_t duration = 0;

            if ((mTotalsample > 0) && (mTableOfContents[0] > 0) && (mSamplesPerFrame > 0)
                    && AMediaFormat_getInt64(mMeta, AMEDIAFORMAT_KEY_DURATION, &duration))
            {
                ape_parser_ctx_t ape_ctx;
                uint32_t filepos, blocks_to_skip;
                ape_ctx.samplerate = mSampleRate;
                ape_ctx.blocksperframe = mSamplesPerFrame;
                ape_ctx.totalframes = mTotalFrame;
                ape_ctx.seektable = mTableOfContents;
                ape_ctx.firstframe = mTableOfContents[0];

                if (ape_calc_seekpos_by_microsecond(&ape_ctx,
                                                    seekTimeUs,
                                                    &newframe,
                                                    &filepos,
                                                    &firstbyte,
                                                    &blocks_to_skip) < 0)
                {
                    ALOGD("getseekto error exit");
                    return AMEDIA_ERROR_UNSUPPORTED;
                }

                mCurrentPos = filepos;
                mCurrentTimeUs = (int64_t)newframe * mSamplesPerFrame * 1000000ll / mSampleRate;

                ALOGD("getseekto seekTimeUs=%lld, Actual time%lld, filepos%lld,frame %d, seekbyte %d", (long long)seekTimeUs, (long long)mCurrentTimeUs, (long long)mCurrentPos, newframe, firstbyte);

            }
            else
            {
                ALOGD("getseekto parameter error exit");
                return AMEDIA_ERROR_UNSUPPORTED;
            }
        }
    }


    if ((mFileoffset != 0)
            && (mCurrentPos >= mFileoffset))
    {
        ALOGD("APESource::readAt to end filesize %lld curr: %lld", (long long)mFileoffset, (long long)mCurrentPos);
        return AMEDIA_ERROR_END_OF_STREAM;
    }

    MediaBufferHelper *buffer;
    status_t err = mBufferGroup->acquire_buffer(&buffer);

    if (err != OK)
    {
        ALOGD("APESource::acquire_buffer fail");
        return AMEDIA_ERROR_UNKNOWN;
    }

    size_t frame_size;
    frame_size = kMaxFrameSize;
    ssize_t n = 0;

    ///frame_size = mMaxBufferSize;
    n = mDataSource->readAt(mCurrentPos, buffer->data(), frame_size);

    ///LOGE("APESource::readAt  %x, %x, %d, %d, %d, %d, %d", mCurrentPos, buffer->data(), buffer->size(), mTotalsample, bitrate, mSampleRate, frame_size);
    //ssize_t n = mDataSource->readAt(mCurrentPos, buffer->data(), frame_size);

    if ((mFileoffset != 0)
            && ((mCurrentPos + n) >= mFileoffset))
    {
        frame_size = mFileoffset - mCurrentPos;
        memset((char *)buffer->data() + frame_size, 0, n - frame_size);
    }
    else if ((n < (ssize_t)frame_size)
             && (n > 0))
    {
        frame_size = n;
        off64_t fileoffset = 0;
        mDataSource->getSize(&fileoffset);
        ALOGD("APESource::readAt not enough read %zd frmsize %zx, filepos %lld, filesize %lld", n, frame_size, (long long)(mCurrentPos + frame_size), (long long)fileoffset);

        //if ((mCurrentPos + frame_size) >= fileoffset
        //        && (mCurrentPos + frame_size) < mTableOfContents[mTotalFrame - 1])
        if ((off64_t)(mCurrentPos + frame_size) >= fileoffset && (mCurrentPos + frame_size) < mTableOfContents[mSt_bound- 1])
        {
            memset(buffer->data(), 0, buffer->size());
            /// for this file is not complete error, frame buffer should not transfer to avoid decoding noise data.
            ALOGD("APESource::file is not enough to end --> memset");
        }
    }
    else if (n <= 0)
    {
        buffer->release();
        buffer = NULL;
        ALOGD("APESource::readAt EOS filepos %lld frmsize %lld", (long long)mCurrentPos, (long long)frame_size);
        return AMEDIA_ERROR_END_OF_STREAM;
    }

    buffer->set_range(0, frame_size);

    AMediaFormat *meta = buffer->meta_data();
    if (options != NULL && options->getSeekTo(&seekTimeUs, &mode))
    {
    	  // Shan:To do
        AMediaFormat_setInt64(meta, AMEDIAFORMAT_KEY_TIME_US, mCurrentTimeUs);
        AMediaFormat_setInt32(meta, "Nem-Frame", newframe);
        AMediaFormat_setInt32(meta, "Seek-Byte", firstbyte);
        //*mSeekbyte = firstbyte;//for ape seek on acodec
        //*mNewframe = newframe;//for ape seek on acodec
    }
    AMediaFormat_setInt64(meta, AMEDIAFORMAT_KEY_TIME_US, mCurrentTimeUs);

    AMediaFormat_setInt32(meta, AMEDIAFORMAT_KEY_IS_SYNC_FRAME, 1);

    mCurrentPos += frame_size;
    mCurrentTimeUs += (int64_t)(frame_size * 8000000ll) / bitrate ;

    *out = buffer;

    ///LOGE("APESource::kKeyTime done %x %lld", mCurrentPos, mCurrentTimeUs);
    return AMEDIA_OK;
}


APEExtractor::APEExtractor(
    DataSourceHelper *source)
    : mInitCheck(NO_INIT),
      mDataSource(source),
      mFirstFramePos(-1),
      mFinalsample(0),
      mSamplesPerFrame(0)
{
    off_t pos = 0;
    ape_parser_ctx_t ape_ctx;
    ape_ctx.seektable = NULL;
    bool success = false;

    ///LOGD("APEExtractor");
    //int64_t meta_offset;
    //uint32_t meta_header;
    success = getAPEInfo(mDataSource, &pos, &ape_ctx, true);

    if (!success)
    {
        return;
    }

    if ((ape_ctx.samplerate <= 0)
            || (ape_ctx.bps <= 0)
            || (ape_ctx.channels <= 0))
    {
        mInitCheck = NO_INIT;
        ALOGD("APEExtractor parameter wrong return samplerate %d bps %d channels %d ", ape_ctx.samplerate, ape_ctx.bps, ape_ctx.channels);
        return;
    }


    mFirstFramePos = pos;
    mTotalsample = ape_ctx.totalsamples;
    mFinalsample = ape_ctx.finalframeblocks;
    mSamplesPerFrame = ape_ctx.blocksperframe;


    unsigned int  in_size = 5184;
    int64_t duration;

    if (ape_ctx.samplerate > 0)
    {
        duration = (int64_t)1000000ll * ape_ctx.totalsamples / ape_ctx.samplerate;
    }
    else
    {
        duration = 0;
    }

    mMeta = AMediaFormat_new();
    AMediaFormat_setString(mMeta, AMEDIAFORMAT_KEY_MIME, MEDIA_MIMETYPE_AUDIO_APE);
    AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_SAMPLE_RATE, ape_ctx.samplerate);
    AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_BIT_RATE, ape_ctx.bps * ape_ctx.channels * ape_ctx.samplerate);
    AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_CHANNEL_COUNT, ape_ctx.channels);

    ALOGV("kKeyDuration set %lld, chn %d", (long long)duration, ape_ctx.channels);
    AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_BITS_PER_SAMPLE, ape_ctx.bps);
    mBps = ape_ctx.bps;

    off64_t fileoffset = 0;
    mDataSource->getSize(&fileoffset);
    mSt_bound = ape_ctx.seektablelength>>2;
    ALOGD("totalframes=%d,seektablelength=%d,mSt_bound=%d",ape_ctx.totalframes,ape_ctx.seektablelength,mSt_bound);
//    if (fileoffset < ape_ctx.seektable[ape_ctx.totalframes - 1])
    if (fileoffset < ape_ctx.seektable[mSt_bound - 1])
    {
        int i = 0;

        //for (i = 0; i < ape_ctx.totalframes; i++)
        for (i = 0; i < mSt_bound; i++)
        {
            if (fileoffset < ape_ctx.seektable[i])
            {
                i--;
                break;
            }
            else if (fileoffset == ape_ctx.seektable[i])
            {
                break;
            }
        }

        duration = (int64_t)1000000ll * i * ape_ctx.blocksperframe / ape_ctx.samplerate;
        ape_ctx.totalframes = i;
        ape_ctx.finalframeblocks = ape_ctx.blocksperframe;
        ALOGD("kKeyDuration redefine duration %lld, totalfrm %d, finalblk %d", (long long)duration, ape_ctx.totalframes, ape_ctx.finalframeblocks);
    }

    AMediaFormat_setInt64(mMeta, AMEDIAFORMAT_KEY_DURATION, duration);

	//AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_APE_FILEVERSION, ape_ctx.fileversion);
	//AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_APE_COMPTYPE, ape_ctx.compressiontype);
	//AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_APE_SAMPSPERFRAM, ape_ctx.blocksperframe);
	//AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_APE_TOTALFRAME, ape_ctx.totalframes);
	//AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_APE_FINALSAMPLE, ape_ctx.finalframeblocks);
    AMediaFormat_setBuffer(mMeta, AMEDIAFORMAT_KEY_CSD_0, &ape_ctx, sizeof(ape_ctx));

    buf_size = in_size * 7; ////ape_ctx.blocksperframe*ape_ctx.channels*ape_ctx.bps/8;

    if (buf_size > 12288)
    {
        buf_size = 12288;    ///12k
    }
	AMediaFormat_setInt32(mMeta, AMEDIAFORMAT_KEY_MAX_INPUT_SIZE, buf_size);

    mTotalFrame = ape_ctx.totalframes;
//    mTableOfContents = (uint32_t *)malloc(mTotalFrame * sizeof(uint32_t));
    mTableOfContents = (uint32_t *)malloc(mSt_bound * sizeof(uint32_t));
    mInitCheck = OK;

    if (mTableOfContents == NULL)
    {
        mInitCheck = NO_INIT;
        ALOGE("APEExtractor has no builtin seektable return ");
    }

    if (mTableOfContents)
    {
        //memcpy(mTableOfContents, ape_ctx.seektable, (mTotalFrame * sizeof(int32_t)));
        memcpy(mTableOfContents, ape_ctx.seektable, mSt_bound* sizeof(int32_t));
    }

    if (ape_ctx.seektable)
    {
        free(ape_ctx.seektable);
    }

    ape_ctx.seektable = NULL;

    ALOGV("APEExtractor done");
}

size_t APEExtractor::countTracks()
{
    return mInitCheck != OK ? 0 : 1;
}

MediaTrackHelper *APEExtractor::getTrack(size_t index)
{
    if (mInitCheck != OK || index != 0)
    {
        return NULL;
    }

    ALOGV("getTrack, %lld, %d, %d, %d, %d", (long long)mFirstFramePos, mTotalsample, mFinalsample,
         mTotalFrame, mSamplesPerFrame);

    return new APESource(
               mMeta, mDataSource, mFirstFramePos, mTotalsample, mFinalsample,
               mTotalFrame, mTableOfContents, mSamplesPerFrame, buf_size,
               mSt_bound,sk_newframe,sk_seekbyte, shouldPlayPCMFloat(mBps));
}

media_status_t APEExtractor::getTrackMetaData(AMediaFormat *meta, size_t index, uint32_t /*flags*/)
{
    if (mInitCheck != OK || index != 0)
    {
        return AMEDIA_ERROR_UNKNOWN;
    }

    return AMediaFormat_copy(meta, mMeta);
}

media_status_t APEExtractor::getMetaData(AMediaFormat *meta)
{
    ALOGV("APEExtractor::getMetaData()");
    AMediaFormat_clear(meta);

    if (mInitCheck != OK) {
        return AMEDIA_ERROR_UNKNOWN;
    }

    AMediaFormat_setString(meta, AMEDIAFORMAT_KEY_MIME, "audio/ape");

    DataSourceHelper helper(mDataSource);
    ID3 id3(&helper);

    if (id3.isValid())
    {
        ALOGE("APEExtractor::getMetaData() ID3 id3");
        struct Map
        {
            const char *key;
            const char *tag1;
            const char *tag2;
        };
        static const Map kMap[] =
        {
            { AMEDIAFORMAT_KEY_ALBUM, "TALB", "TAL" },
            { AMEDIAFORMAT_KEY_ARTIST, "TPE1", "TP1" },
            { AMEDIAFORMAT_KEY_ALBUMARTIST, "TPE2", "TP2" },
            { AMEDIAFORMAT_KEY_COMPOSER, "TCOM", "TCM" },
            { AMEDIAFORMAT_KEY_GENRE, "TCON", "TCO" },
            { AMEDIAFORMAT_KEY_TITLE, "TIT2", "TT2" },
            { AMEDIAFORMAT_KEY_YEAR, "TYE", "TYER" },
            { AMEDIAFORMAT_KEY_AUTHOR, "TXT", "TEXT" },
            { AMEDIAFORMAT_KEY_CDTRACKNUMBER, "TRK", "TRCK" },
            { AMEDIAFORMAT_KEY_DISCNUMBER, "TPA", "TPOS" },
            { AMEDIAFORMAT_KEY_COMPILATION, "TCP", "TCMP" },
        };
        static const size_t kNumMapEntries = sizeof(kMap) / sizeof(kMap[0]);

        for (size_t i = 0; i < kNumMapEntries; ++i)
        {
            ///LOGE("getMetaData() id3 kMap %d, %d", kNumMapEntries, i);
            ID3::Iterator *it = new ID3::Iterator(id3, kMap[i].tag1);

            if (it->done())
            {
                delete it;
                it = new ID3::Iterator(id3, kMap[i].tag2);
            }

            if (it->done())
            {
                delete it;
                continue;
            }

            String8 s;
            it->getString(&s);
            delete it;

            AMediaFormat_setString(meta, kMap[i].key, s.string());
        }

        size_t dataSize;
        String8 mime;
        const void *data = id3.getAlbumArt(&dataSize, &mime);

        if (data) {
            AMediaFormat_setBuffer(meta, AMEDIAFORMAT_KEY_ALBUMART, data, dataSize);
        }

        return AMEDIA_OK;

    }

    APETAG apetag(&helper);

    if (apetag.isValid())
    {

        struct ApeMap
        {
            const char *key;
            const char *tag;
            uint16_t    key_len;
            uint32_t    key_attr;
        };
        static const ApeMap kMap[] =
        {
            { AMEDIAFORMAT_KEY_ALBUM,        "Album",    5,  META_TAG_ATTR_ALBUM },
            { AMEDIAFORMAT_KEY_ARTIST,       "Artist",   6,  META_TAG_ATTR_ARTIST },
            { AMEDIAFORMAT_KEY_COMPOSER,     "Composer", 7,  META_TAG_ATTR_AUTHOR },
            { AMEDIAFORMAT_KEY_GENRE,        "Genre",    5,  META_TAG_ATTR_GENRE },
            { AMEDIAFORMAT_KEY_TITLE,        "Title",    5,  META_TAG_ATTR_TITLE },
            { AMEDIAFORMAT_KEY_YEAR,         "Year",     4,  META_TAG_ATTR_YEAR },
            { AMEDIAFORMAT_KEY_CDTRACKNUMBER, "Track",    5,  META_TAG_ATTR_TRACKNUM },
        };

        static const size_t kNumMapEntries = sizeof(kMap) / sizeof(kMap[0]);

        for (size_t i = 0; i < kNumMapEntries; ++i)
        {
            APETAG::Iterator *it = new APETAG::Iterator(apetag, kMap[i].tag, kMap[i].key_len);

            if (it->done())
            {
                delete it;
                continue;
            }

            String8 s;
            it->getString(&s);
            delete it;

            AMediaFormat_setString(meta, kMap[i].key, s.string());
        }

        return AMEDIA_OK;

    }

    return AMEDIA_OK;
}

static CMediaExtractor* CreateExtractor(
        CDataSource *source,
        void *) {
    return wrap(new APEExtractor(new DataSourceHelper(source)));
}

static CreatorFunc Sniff(
        CDataSource *source, float *confidence, void **,
        FreeMetaFunc *) {
    off_t pos = 0;

    DataSourceHelper helper(source);
    ape_parser_ctx_t ape_ctx;
    if (!getAPEInfo(&helper, &pos, &ape_ctx, false))
    {
        return NULL;
    }

    *confidence = 0.3f;

    return CreateExtractor;
}

static const char *extensions[] = {
    "ape",
    NULL
};

extern "C" {
// This is the only symbol that needs to be exported
__attribute__ ((visibility ("default")))
ExtractorDef GETEXTRACTORDEF() {
    return {
        EXTRACTORDEF_VERSION,
        UUID("5e7bcb04-9cd2-427e-9da5-7abf2f24ace5"),
        1, // version
        "MtkAPE Extractor",
        { .v3 = {Sniff, extensions} },
    };
}

} // extern "C"

}  // namespace android
