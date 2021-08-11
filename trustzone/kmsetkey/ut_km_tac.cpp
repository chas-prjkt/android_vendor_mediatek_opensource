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

#define IMSG_TAG "ut_kmsetkey"

#include "tee_client_api.h"
#include <string.h>
#include "imsg_log.h"
#include "ut_km_tac.h"
#include <log/log.h>

#define ATTESTKEY_FLAG 0xaf015838

static const char* host_name = "bta_loader";

static const TEEC_UUID KEYBOX_UUID =  { 0xd91f322a, 0xd5a4, 0x41d5, { 0x95, 0x51, 0x10, 0xed, 0xa3, 0x27, 0x2f, 0xc0 } };


int ut_km_import_google_key(unsigned char *data, unsigned int datalen)
{
    if (data == NULL || datalen == 0)
        return -1;

    TEEC_Context context;
    TEEC_Session session ;
    TEEC_Operation operation ;
	TEEC_SharedMemory inputSM;
    TEEC_Result result;
    uint32_t returnOrigin = 0;

    memset((void *)&context, 0, sizeof(TEEC_Context));
    memset((void *)&session, 0, sizeof(TEEC_Session));
    memset((void *)&operation, 0, sizeof(TEEC_Operation));

    result = TEEC_InitializeContext(host_name, &context);
    if(result != TEEC_SUCCESS) {
		IMSG_ERROR("TEEC_InitializeContext FAILED, err:%x",result);
        goto cleanup_1;
    }

    result = TEEC_OpenSession(
            &context,
            &session,
            &KEYBOX_UUID,
            TEEC_LOGIN_PUBLIC,
            NULL,
            NULL,
            &returnOrigin);
    if(result != TEEC_SUCCESS) {
		IMSG_ERROR("TEEC_OpenSession FAILED, err:%x",result);
        goto cleanup_2;
    }

	inputSM.size = datalen;
	inputSM.flags = TEEC_MEM_INPUT;
	result = TEEC_AllocateSharedMemory(&context, &inputSM);
	if (result != TEEC_SUCCESS || inputSM.buffer == 0) {
		IMSG_ERROR("TEEC_AllocateSharedMemory FAILED, err:%x",result);
		goto cleanup_3;
	}


	memset(inputSM.buffer, 0, inputSM.size);
	memcpy(inputSM.buffer, data, datalen);

	operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT,
			TEEC_MEMREF_PARTIAL_INPUT, TEEC_NONE, TEEC_NONE);

	operation.params[1].memref.parent = &inputSM;
	operation.params[1].memref.offset = 0;
	operation.params[1].memref.size = inputSM.size;
    operation.started = 1;

    result = TEEC_InvokeCommand(&session,0,&operation,NULL);
    if (result != TEEC_SUCCESS) {
		IMSG_ERROR("TEEC_InvokeCommand FAILED, err:%x",result);
        goto cleanup_4;
    }

    result = operation.params[0].value.a;
    if (result != TEEC_SUCCESS) {
        IMSG_ERROR("ta busness error, %d", result);
    }

	cleanup_4:
        TEEC_ReleaseSharedMemory(&inputSM);
    cleanup_3:
        TEEC_CloseSession(&session);
    cleanup_2:
        TEEC_FinalizeContext(&context);
    cleanup_1:
        return result;
}

int ut_km_check_google_key(void)
{
    TEEC_Context context;
    TEEC_Session session ;
    TEEC_Operation operation ;
    TEEC_Result result;
    uint32_t returnOrigin = 0;

    memset((void *)&context, 0, sizeof(TEEC_Context));
    memset((void *)&session, 0, sizeof(TEEC_Session));
    memset((void *)&operation, 0, sizeof(TEEC_Operation));
    ALOGI("ut_km_check_google_key start");

    result = TEEC_InitializeContext(host_name, &context);
    if(result != TEEC_SUCCESS) {
		IMSG_ERROR("TEEC_InitializeContext FAILED, err:%x",result);
        goto cleanup_1;
    }
    ALOGI("ut_km_check_google_key 0");

    result = TEEC_OpenSession(
            &context,
            &session,
            &KEYBOX_UUID,
            TEEC_LOGIN_PUBLIC,
            NULL,
            NULL,
            &returnOrigin);
    if(result != TEEC_SUCCESS) {
		IMSG_ERROR("TEEC_OpenSession FAILED, err:%x",result);
        goto cleanup_2;
    }


    ALOGI("ut_km_check_google_key 1");
	operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT,
			TEEC_NONE, TEEC_NONE, TEEC_NONE);

    operation.started = 1;

    result = TEEC_InvokeCommand(&session, 101, &operation, NULL);
    if (result != TEEC_SUCCESS) {
		IMSG_ERROR("TEEC_InvokeCommand FAILED, err:%x",result);
        goto cleanup_3;
    }
    ALOGI("ut_km_check_google_key 2");

    result = operation.params[0].value.a;
    if (result != ATTESTKEY_FLAG) {
        ALOGE("keybox not install, %d", result);
        result = -1;
        goto cleanup_3;
    }

    ALOGI("keybox already install, %08x, %08x", result, ATTESTKEY_FLAG);
    result = 0;

    cleanup_3:
        TEEC_CloseSession(&session);
    cleanup_2:
        TEEC_FinalizeContext(&context);
    cleanup_1:
        return result;
}
