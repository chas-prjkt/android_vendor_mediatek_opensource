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

#ifndef CIPHERFILEUTIL_H_
#define CIPHERFILEUTIL_H_

#include <utils/String8.h>
#include <stdio.h>

namespace android
{

class CryptoHelper;

class CipherFileUtil
{
public:
    /*
     * Read {byte_num} bytes from cipher file (DCF) referred by {fd}.
     *
     * Parameter:
     *     fd:          linux file descriptor
     *     buf:         buffer for storing the bytes read (after decryption).
     *     byte_num:    the desired number of bytes to read.
     *     offset:      the start position to read (from the beginning of REAL content)
     *     data_offset: the position of the beginning of content in whole DCF file.
     *     data_size:   the size of content (in bytes).
     *     hlp:         the CryptoHelper object used for decryption.
     *
     * Return value:
     *     The actual number of bytes which have been read (after decryption).
     *     0 or -1 if the reading operation fails.
     *
     * Remarks:
     *     1. The DCF file, is consist of the header & the content. the function
     *        only reads desired bytes from the content part, and the decrypted
     *        raw data is returned in {buf}.
     *
     *     2. DCF file uses AES128CBC encryption. Although there's a 16-bytes IV (Initial Vector)
     *        at the beginning of the content part, you are really specifying the {offset} from
     *        the BEGINNING OF the raw data (not encrypted), not considering the IV.
     */
    static int CipherFileRead(int fd, void* buf, int byte_num, int offset,
                              int data_offset, int data_size, CryptoHelper& hlp);

    // Add for Decode image with open decrypt seesion with ashmem
    static int CipherFileRead(char* data, void* buf, int byte_num, int offset,
                                   int data_offset, int data_size, CryptoHelper& hlp);

    static int CipherFileDump(int fd, int data_offset, int data_size, CryptoHelper& hlp); // deprecated

    static int CipherFileDump(String8 file_name, int fd, int data_offset, int data_size, CryptoHelper& hlp);

    /*
     * Encrypt the data of the file referred by {origin} and save the encryted data to the file referred by {out}.
     *
     * Parameter:
     *     origin:         file to be encrypted.
     *     data_offset:    the offset of data to be encrypted.
     *     data_size:      the length of data to be encrypted.
     *     out:            file where to save the encryted data.
     *     hlp:            the CryptoHelper object used for encryption.
     *     iv:             initial vector
     *
     * Return value:
     *     0 for succeed while -1 for failure.
     */
    static int CipherFileInstall(FILE* origin, int data_offset, int data_size, FILE* out,
                                 CryptoHelper& hlp, unsigned char* iv);
private:
    static bool isEnableDebug();
private:
    static bool sDebug;
};

} // namespace android

#endif /* CIPHERFILEUTIL_H_ */
