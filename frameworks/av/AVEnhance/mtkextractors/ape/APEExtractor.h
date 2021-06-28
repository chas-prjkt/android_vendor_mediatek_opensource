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

#ifndef APE_EXTRACTOR_H_

#define APE_EXTRACTOR_H_

#include <media/MediaExtractorPluginApi.h>
#include <media/MediaExtractorPluginHelper.h>

namespace android
{
///#ifndef ANDROID_DEFAULT_CODE

#define APE_MIN_VERSION 3950 /* originally set to 3970, but 3950 should work */
#define APE_MAX_VERSION 4100
#define APE_MAX_COMPRESS 4000


#define MAC_FORMAT_FLAG_8_BIT                 1    // is 8-bit [OBSOLETE]
#define MAC_FORMAT_FLAG_CRC                   2    // uses the new CRC32 error detection [OBSOLETE]
#define MAC_FORMAT_FLAG_HAS_PEAK_LEVEL        4    // uint32 nPeakLevel after the header [OBSOLETE]
#define MAC_FORMAT_FLAG_24_BIT                8    // is 24-bit [OBSOLETE]
#define MAC_FORMAT_FLAG_HAS_SEEK_ELEMENTS    16    // has the number of seek elements after the peak level
#define MAC_FORMAT_FLAG_CREATE_WAV_HEADER    32    // create the wave header on decompression (not stored)


#define MIN_RANDOM_FRAMES_TO_SCAN 4
#define MIN_RANDOM_LOCATION_TO_SCAN 30

#define ape_parser_uint32_t unsigned int
#define ape_parser_uint16_t unsigned short
#define ape_parser_uint8_t  unsigned char
#define ape_parser_int32_t signed int
#define ape_parser_int16_t signed short
#define ape_parser_int8_t  signed char

struct ape_parser_ctx_t
{
    /* Derived fields */
    ape_parser_uint32_t      junklength;
    ape_parser_uint32_t      firstframe;
    ape_parser_uint32_t      totalsamples;

    /* Info from Descriptor Block */
    char                     magic[4];
    ape_parser_uint16_t       fileversion;
    ape_parser_uint16_t       padding1;
    ape_parser_uint32_t      descriptorlength;
    ape_parser_uint32_t      headerlength;
    ape_parser_uint32_t      seektablelength;
    ape_parser_uint32_t      wavheaderlength;
    ape_parser_uint32_t      audiodatalength;
    ape_parser_uint32_t      audiodatalength_high;
    ape_parser_uint32_t      wavtaillength;
    ape_parser_uint8_t       md5[16];

    /* Info from Header Block */
    ape_parser_uint16_t      compressiontype;
    ape_parser_uint16_t      formatflags;
    ape_parser_int32_t      blocksperframe;
    ape_parser_uint32_t      finalframeblocks;
    ape_parser_uint32_t      totalframes;
    ape_parser_uint16_t      bps;
    ape_parser_uint16_t      channels;
    ape_parser_uint32_t      samplerate;

    int                      seektablefilepos; /* Location in .ape file of seektable */
    uint32_t                *seektable;        /* Seektable buffer */

};



///#endif
struct AMessage;
class String8;

class APEExtractor : public MediaExtractorPluginHelper
{
public:
    // Extractor assumes ownership of "source".
    APEExtractor(DataSourceHelper *source);

    virtual size_t countTracks();
    virtual MediaTrackHelper *getTrack(size_t index);
    virtual media_status_t getTrackMetaData(AMediaFormat *meta, size_t index, uint32_t flags);
    virtual media_status_t getMetaData(AMediaFormat *meta);
    virtual const char* name() { return "APEExtractor"; }
    uint32_t *sk_newframe;
    uint32_t *sk_seekbyte;

private:

    APEExtractor(const APEExtractor &);
    APEExtractor &operator=(const APEExtractor &);

    status_t mInitCheck;
    DataSourceHelper *mDataSource;
    AMediaFormat *mMeta;
    off_t mFirstFramePos;
    uint32_t mTotalsample;
    uint32_t mFinalsample;
    uint32_t mFixedHeader;
    int32_t mTotalFrame; // total number of bytes in this MP3
    uint32_t *mTableOfContents; // TOC entries in XING header
    int mSamplesPerFrame;
    int32_t mAvgBitrateInbpsFromRandomScan;
    int32_t buf_size ;
//seektable upper bound
    int32_t mSt_bound;
    int32_t mBps;

};

bool SniffAPE(
    DataSourceHelper *source, String8 *mimeType, float *confidence,
    sp<AMessage> *meta);

}  // namespace android

#endif  // APE_EXTRACTOR_H_
