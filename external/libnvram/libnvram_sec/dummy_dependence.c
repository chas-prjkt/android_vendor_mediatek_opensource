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

#include "libnvram_sec.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//typedef struct
//{
//   unsigned char data[NVRAM_CIPHER_LEN];
//   unsigned int ret;sss

//} META_CONTEXT;

/******************************************************************************
 *  EXPORT FUNCTIONS
 ******************************************************************************/
int sec_nvram_enc (META_CONTEXT *meta_ctx) {
	return 0;
}
int sec_nvram_dec (META_CONTEXT *meta_ctx) {
	return 0;
}
