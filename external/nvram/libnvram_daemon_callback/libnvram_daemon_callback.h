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

#ifndef __LIBNVRAM_DAEMON_CALLBACK_H
#define __LIBNVRAM_DAEMON_CALLBACK_H

#include "libnvram.h"
#include "libnvram_log.h"
#include "CFG_file_public.h"
#include "CFG_file_lid.h"
#include "Custom_NvRam_LID.h"

#ifdef __cplusplus
extern "C"
{
#endif

int my_callback(void);
int init_callback(void);


#ifdef __cplusplus
}
#endif


#endif //__NVRAM_LIB_H
