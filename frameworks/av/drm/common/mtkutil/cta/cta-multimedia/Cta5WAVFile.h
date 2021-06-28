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

#ifndef __CTA5_WAV_FILE_H__
#define __CTA5_WAV_FILE_H__

#include <Cta5File.h>
#include <Cta5CommonMultimediaFile.h>

namespace android
{

/**
 * This class is used to construct a CTA5 common multimedia file
 * If you want to parse a CTA5 file, the class is your beset choice
 * If you want to Convert a normal file to a CTA5 file, this class is your best choice
 * This class is a super class, and it's used for most multimedia fils which only has one header.
 * If you want to convert other multimedia files which have two or more headers,
 * you need to create a new class and implented from Cta5CommonMultimediaFile
 */
class Cta5WAVFile : public Cta5CommonMultimediaFile
{
public:
    Cta5WAVFile(int fd,String8 key);

    //This constructor is useful when you want to get a Cta5 file format
    //To convert a normal file to a CTA5 file, you may need this version
    Cta5WAVFile(String8 mimeType, String8 cid, String8 dcfFlHeaders, uint64_t datatLen, String8 key);

    //Now dcf header is no need
    Cta5WAVFile(String8 mimeType, uint64_t datatLen, String8 key);
public:
    virtual ~Cta5WAVFile(){}
    /*
        * This function is used to parse all main header of specified multimedia files
        * the result is one or more header offset and size
        */
    virtual bool parseHeaders(int fd);

private:
    // status_t mInitCheck = 0;
    bool mValidFormat = false;
    uint16_t mWaveFormat = 0;
    uint16_t mNumChannels = 0;
    uint32_t mChannelMask = 0;
    uint32_t mSampleRate = 0;
    uint16_t mBitsPerSample = 0;
    off64_t mDataOffset = 0;
    size_t mDataSize = 0;
    uint32_t mAvgBytesPerSec = 0;
    uint32_t mBlockAlign = 0;
#ifdef AUDIO_ADPCM_SUPPORT
    uint32_t mExtraDataSize = 0;
    uint8_t* mpExtraData = NULL;
#endif
    uint32_t mSamplesPerBlock = 0;
    uint32_t mSamplesNumberPerChannel = 0;
    // uint64_t mBlockDurationUs = 0;
};
}
#endif //__CTA5_WAV_FILE_H__
