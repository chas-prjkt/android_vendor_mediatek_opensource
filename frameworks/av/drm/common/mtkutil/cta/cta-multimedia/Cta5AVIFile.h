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

#ifndef __CTA5_AVI_FILE_H__
#define __CTA5_AVI_FILE_H__

#include <Cta5File.h>
#include <Cta5CommonMultimediaFile.h>

namespace android
{

struct riffList {
    uint32_t ID;
    uint32_t size;
    uint32_t type;
};

// big endian fourcc
#define BFOURCC(c1, c2, c3, c4) \
    (c4 << 24 | c3 << 16 | c2 << 8 | c1)

#define FORMATFOURCC "0x%08x:%c%c%c%c"
#define PRINTFOURCC(x) x,((uint8_t*)&x)[0],((uint8_t*)&x)[1],((uint8_t*)&x)[2],((uint8_t*)&x)[3]
// size of chunk should be WORD align
#define EVEN(i) (uint32_t)((i) + ((i) & 1))

/**
 * This class is used to construct a CTA5 common multimedia file
 * If you want to parse a CTA5 file, the class is your beset choice
 * If you want to Convert a normal file to a CTA5 file, this class is your best choice
 * This class is a super class, and it's used for most multimedia fils which only has one header.
 * If you want to convert other multimedia files which have two or more headers,
 * you need to create a new class and implented from Cta5CommonMultimediaFile
 */
class Cta5AVIFile : public Cta5CommonMultimediaFile
{
public:
    Cta5AVIFile(int fd,String8 key);

    //This constructor is useful when you want to get a Cta5 file format
    //To convert a normal file to a CTA5 file, you may need this version
    Cta5AVIFile(String8 mimeType, String8 cid, String8 dcfFlHeaders, uint64_t datatLen, String8 key);

    //Now dcf header is no need
    Cta5AVIFile(String8 mimeType, uint64_t datatLen, String8 key);
public:
    virtual ~Cta5AVIFile(){}
    /*
        * This function is used to parse all main header of specified multimedia files
        * the result is one or more header offset and size
        */
    virtual bool parseHeaders(int fd);

};
}
#endif //__CTA5_AVI_FILE_H__
