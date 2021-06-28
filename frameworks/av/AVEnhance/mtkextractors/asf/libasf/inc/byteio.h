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

#ifndef BYTEIO_H
#define BYTEIO_H

#ifndef ASF_H
#include "asf.h"
#endif

class ASFByteIO {
public:
    static uint16_t asf_byteio_getWLE(uint8_t *data);
    static uint32_t asf_byteio_getDWLE(uint8_t *data);
    static uint64_t asf_byteio_getQWLE(uint8_t *data);
    static void asf_byteio_getGUID(asf_guid_t *guid, uint8_t *data);
    static void asf_byteio_get_string(uint16_t *string, uint16_t strlen, uint8_t *data);
    static int asf_byteio_read(uint8_t *data, int size, asf_iostream_t *iostream);
};

#endif
