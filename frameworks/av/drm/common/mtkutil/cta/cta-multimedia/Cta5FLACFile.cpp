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
#define LOG_TAG "Cta5FLACFile"
#include <utils/Log.h>

#include <Cta5FLACFile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

using namespace android;

Cta5FLACFile::Cta5FLACFile(int fd, String8 key) : Cta5CommonMultimediaFile(fd, key)
{
    ALOGD("Cta5APEFile(fd, key)");
}

//This constructor is useful when you want to get a Cta5 file format
//To convert a normal file to a CTA5 file, you may need this version
Cta5FLACFile::Cta5FLACFile(String8 mimeType, String8 cid, String8 dcfFlHeaders,
        uint64_t datatLen, String8 key) :
        Cta5CommonMultimediaFile(mimeType, cid, dcfFlHeaders, datatLen, key)
{
    ALOGD("Cta5FLACFile(mimeType, cid, dcfFlHeaders, datatLen, key)");
}

Cta5FLACFile::Cta5FLACFile(String8 mimeType, uint64_t datatLen, String8 key) :
        Cta5CommonMultimediaFile(mimeType, datatLen, key)
{
    ALOGD("Cta5FLACFile(mimeType, datatLen, key)");
}

// flac + streaminfo
bool Cta5FLACFile::parseHeaders(int fd) {
    ALOGD("parseHeaders()");

    // flac
    uint8_t magic[4];
    if (DrmCtaMultiMediaUtil::readAt(
                fd, 0, magic, sizeof(magic)) < (ssize_t)sizeof(magic)) {
        ALOGE("[ERROR][CTA5]read magic fail");
        return false;
    }
    if (0 != memcmp(magic, "fLaC", 4)) {
        ALOGE("[ERROR][CTA5]magic is not flac]");
        return false;
    }

    // streaminfo
    uint8_t block_header[4];
    if (DrmCtaMultiMediaUtil::readAt(
                fd, 4, block_header, sizeof(block_header)) < (ssize_t)sizeof(block_header)) {
        ALOGE("[ERROR][CTA5]read block header fail");
        return false;
    }

    if (block_header[0] != 0x00) {
        ALOGE("[ERROR][CTA5]not streaminfo metadata block");
        return false;
    }

    // read block header size
    uint32_t header_size = block_header[1] << 16 | block_header[2] << 8 | block_header[3];
    ALOGD("the streaminfo block header size is %d", header_size);

    off64_t flac_header_offset = 0ll;
    off64_t flac_header_size = header_size + sizeof(magic) + sizeof(block_header);
    ALOGD("found flac header, offset[%ld], size[%ld]", (long) flac_header_offset, (long) flac_header_size);

    // stored header information into Vector<header>
    Header * flac_header = new Header();
    flac_header->clear_header_offset = flac_header_offset;
    flac_header->clear_header_size = flac_header_size;

    mHeaders.push_back(flac_header);

    return true;
}
