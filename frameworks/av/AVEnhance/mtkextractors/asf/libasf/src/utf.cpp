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

//#include <stdlib.h>

#ifndef ASFPARSER_H_INCLUDED
#include "asfparser.h"
#endif

#include <stdlib.h>
/**
 * Decode UTF-16LE text from buffer of buflen size and
 * allocate a new buffer containing the same string
 * encoded as UTF-8. Supports characters outside of BMP
 * encoded as an UTF-16 surrogate pair. Returns NULL in
 * case of allocation failure or invalid surrogate pair.
 * Buflen is in bytes.
 */
char * ASFParser::asf_utf8_from_utf16le(uint8_t *buf, uint16_t buflen) {
    uint32_t length, pos;
    char *ret;
    int i;

    length = 0;
    for (i=0; i<buflen/2; i++) {
        uint16_t wchar1, wchar2;

        wchar1 = ASFByteIO::asf_byteio_getWLE(&buf[i*2]);
        if (wchar1 >= 0xD800 && wchar1 < 0xDB00) {
            i++;

            if (i*2 >= buflen) {
                /* unexpected end of buffer */
                return NULL;
            }
            wchar2 = ASFByteIO::asf_byteio_getWLE(&buf[i*2]);
            if (wchar2 < 0xDB00 || wchar2 > 0xDFFF) {
                /* invalid surrogate pair */
                return NULL;
            }
            length += 4;
        } else if (wchar1 > 0x07FF) {
            length += 3;
        } else if (wchar1 > 0x7F) {
            length += 2;
        } else {
            length++;
        }
    }

    ret = (char*)malloc(length + 1);
    if (!ret) {
        return NULL;
    }

    pos = 0;
    for (i=0; i<buflen/2; i++) {
        uint16_t wchar1, wchar2;
        uint32_t codepoint;

        wchar1 = ASFByteIO::asf_byteio_getWLE(&buf[i*2]);
        if (wchar1 >= 0xD800 && wchar1 < 0xDB00) {
            i++;
            wchar2 = ASFByteIO::asf_byteio_getWLE(&buf[i*2]);
            codepoint = 0x10000;
            codepoint += ((wchar1 & 0x03FF) << 10);
            codepoint |=  (wchar2 & 0x03FF);
        } else {
            codepoint = wchar1;
        }

        if (codepoint > 0xFFFF) {
            ret[pos++] = 0xF0 | ((codepoint >> 18) & 0x07);
            ret[pos++] = 0x80 | ((codepoint >> 12) & 0x3F);
            ret[pos++] = 0x80 | ((codepoint >> 6)  & 0x3F);
            ret[pos++] = 0x80 |  (codepoint & 0x3F);
        } else if (codepoint > 0x07FF) {
            ret[pos++] = 0xE0 |  (codepoint >> 12);
            ret[pos++] = 0x80 | ((codepoint >> 6) & 0x3F);
            ret[pos++] = 0x80 |  (codepoint & 0x3F);
        } else if (codepoint > 0x7F) {
            ret[pos++] = 0xC0 |  (codepoint >> 6);
            ret[pos++] = 0x80 |  (codepoint & 0x3F);
        } else {
            ret[pos++] = codepoint;
        }
    }

    ret[length] = '\0';
    return ret;
}
