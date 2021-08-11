/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef HARDWARE_KMSETKEY_H
#define HARDWARE_KMSETKEY_H

#include <hardware/hardware.h>

#define HARDWARE_KMSETKEY "kmsetkey"
#define KMSETKEY_HARDWARE_MODULE_ID "kmsetkey"

struct kmsetkey_device {
	hw_device_t common;

	int (*attest_key_install)(const uint8_t *peakb, const uint32_t peakb_len);
	int (*attest_key_check)(const uint8_t *peakb, const uint32_t peakb_len);
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

#endif
