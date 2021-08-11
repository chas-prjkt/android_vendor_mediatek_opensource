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

#define IMSG_TAG "microkeymaster"

#include <errno.h>
#include <imsg_log.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "ut_km_def.h"
#include "ut_km_ioctl.h"
#include "ut_km_api.h"
#include "ipc/keymaster_ipc.h"

unsigned char* keymaster_buffer = NULL;

int TEE_Alloc_KM_Buffer_And_Reset() {
    /* allocate for the first time */
    if (keymaster_buffer == NULL) {
        keymaster_buffer = (unsigned char*)malloc(KEYMASTER_MAX_BUFFER_LENGTH);

        if (keymaster_buffer == NULL) {
            IMSG_ERROR("malloc keymaster buffer failed");
            return -1;
        }
    }

    /* always reset */
    memset(keymaster_buffer, 0, KEYMASTER_MAX_BUFFER_LENGTH);
    return 0;
}

void TEE_Free_KM_Buffer(void) {
    if (keymaster_buffer != NULL) {
        free(keymaster_buffer);
        keymaster_buffer = NULL;
    }
}
