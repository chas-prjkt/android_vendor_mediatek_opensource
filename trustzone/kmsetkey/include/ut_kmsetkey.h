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

#ifndef __UT_KM_SETKEY_H__
#define __UT_KM_SETKEY_H__

#include <stdbool.h>
#include <stdint.h>
#include <hardware/hardware.h>

#define KMSETKEY_HARDWARE_MODULE_NAME "Hardware kmsetkey HAL"
#define KMSETKEY_HARDWARE_MODULE_ID "kmsetkey"
#define HARDWARE_KMSETKEY "kmsetkey"
#define KMSETKEY_MODULE_API_VERSION_0_1 HARDWARE_MODULE_API_VERSION(0, 1)

typedef enum {
    KMSK_ERROR_OK = 0,
    KMSK_ERROR_UNEXPECTED_NULL_POINTER = -1,
    KMSK_ERROR_MEMORY_ALLOCATION_FAILED = -2,
    KMSK_ERROR_RESPONSE_ERROR = -3,
    KMSK_ERROR_INVOKE_COMMAND_FAILED = -4,

    KMSK_ERROR_KEY_NOT_EXIST = -100,

    KMSK_ERROR_UNKNOWN_ERROR = -1000,
} kmsetkey_error_t;

struct kmsetkey_module {

	hw_module_t common;
};

struct kmsetkey_device {

	hw_device_t common;
	kmsetkey_error_t (*attest_key_install)(const uint8_t *peakb, const uint32_t peakb_len);
    kmsetkey_error_t (*attest_key_check)(const uint8_t *peakb, const uint32_t peakb_len);
};

typedef struct kmsetkey_device kmsetkey_device_t;

static inline int kmsetkey_open(const struct hw_module_t *module, kmsetkey_device_t **device)
{
    if (module == nullptr)
        return -1;

    return module->methods->open(module, HARDWARE_KMSETKEY, (struct hw_device_t **)device);
}

static inline int kmsetkey_close(kmsetkey_device_t *device)
{
    if (device == nullptr)
        return -1;

    return device->common.close(&device->common);
}


#endif //__UT_KM_SETKEY_H__
