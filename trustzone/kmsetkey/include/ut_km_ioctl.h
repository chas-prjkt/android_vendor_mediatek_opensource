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

#ifndef __UT_KEYMASTER_IOCTL_H__
#define __UT_KEYMASTER_IOCTL_H__

__BEGIN_DECLS

#include <stdbool.h>
#include <stdint.h>

#define TEEI_IOC_MAGIC 'T'
#define CMD_KM_MEM_CLEAR _IO(TEEI_IOC_MAGIC, 0x1)
#define CMD_KM_MEM_SEND _IO(TEEI_IOC_MAGIC, 0x2)

extern unsigned char* keymaster_buffer;

int TEE_InvokeCommand(void);
int TEE_Alloc_KM_Buffer_And_Reset();
void TEE_Free_KM_Buffer(void);

__END_DECLS

#endif //__UT_KEYMASTER_IOCTL_H__
