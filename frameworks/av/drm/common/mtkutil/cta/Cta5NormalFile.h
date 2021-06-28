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

#ifndef __DRM_CTA5_NORMAL_FILE_H__
#define __DRM_CTA5_NORMAL_FILE_H__

#include <Cta5File.h>
#include <DrmCtaUtil.h>

namespace android
{
/**
 * This class is used to construct a CTA5 Normal file
 * If you want to parse a CTA5 file, the class is your beset choice
 * If you want to Convert a normal file to a CTA5 file, this class is your best choice
 */
class Cta5NormalFile : public Cta5File
{
public:
    Cta5NormalFile(int fd, String8 key);

    //This constructor is useful when you want to get a Cta5 file format
    //To convert a normal file to a CTA5 file, you may need this version
    Cta5NormalFile(String8 mimeType, String8 cid, String8 dcfFlHeaders, uint64_t datatLen,
            String8 key);

    Cta5NormalFile(String8 mimeType, uint64_t datatLen,
               String8 key);

    ssize_t readCipherFile(int fd, void* buffer, int numBytes, int offset, int cipher_content_offset, int cipher_content_size);
public:
    virtual ~Cta5NormalFile(){}
    /**
     * Encrypt fd_in to fd_out, fd_out should include the cta5 file header
     * And notify the encrypt progress by calling infoListener
     */
    virtual bool encrypt(int fd_in, int fd_out,const Vector<DrmCtaUtil::Listener> *infoListener);
    /**
     * Decrypt current cta5 file to fd_out
     * And notify the encrypt progress by calling infoListener
     */
    virtual bool decrypt(int fd_out,const Vector<DrmCtaUtil::Listener> *infoListener);
    /*
     * This function is used for playing a multimedia decrypted file with pre-decrypt
     */
    virtual int64_t pread(void* buf, uint64_t size, off64_t offset);
};

}
#endif //__DRM_CTA5_NORMAL_FILE_H__
