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

#include "byteio.h"

uint16_t ASFByteIO::asf_byteio_getWLE(uint8_t *data) {
    uint16_t ret;
    int i;
    for (i=1, ret=0; i>=0; i--) {
        ret <<= 8;
        ret |= data[i];
    }
    return ret;
}

uint32_t ASFByteIO::asf_byteio_getDWLE(uint8_t *data) {
    uint32_t ret;
    int i;

    for (i=3, ret=0; i>=0; i--) {
        ret <<= 8;
        ret |= data[i];
    }

    return ret;
}

uint64_t ASFByteIO::asf_byteio_getQWLE(uint8_t *data) {
    uint64_t ret;
    int i;

    for (i=7, ret=0; i>=0; i--) {
        ret <<= 8;
        ret |= data[i];
    }

    return ret;
}

void ASFByteIO::asf_byteio_getGUID(asf_guid_t *guid, uint8_t *data) {
    guid->v1 = asf_byteio_getDWLE(data);
    guid->v2 = asf_byteio_getWLE(data + 4);
    guid->v3 = asf_byteio_getWLE(data + 6);
    memcpy(guid->v4, data + 8, 8);
}

void ASFByteIO::asf_byteio_get_string(uint16_t *string, uint16_t strlen, uint8_t *data) {
    int i;

    if (!data || !string) return;

    for (i=0; i<strlen; i++) {
        string[i] = asf_byteio_getWLE(data + i*2);
    }
}

int ASFByteIO::asf_byteio_read(uint8_t *data, int size, asf_iostream_t *iostream) {
    int read = 0, tmp;

    if (!iostream || !data || !iostream->read || !iostream->source || (size < 0)) {
        return ASF_ERROR_INTERNAL;
    }

    while ((tmp = iostream->read(iostream->source, data+read, size-read)) > 0) {
        read += tmp;

        if (read == size) {
            return read;
        }
    }

    return (tmp == 0) ? ASF_ERROR_EOF : ASF_ERROR_IO;
}
