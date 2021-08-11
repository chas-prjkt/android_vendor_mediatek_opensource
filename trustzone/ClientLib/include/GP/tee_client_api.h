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

/*
 * This header file corresponds to V1.0 of the GlobalPlatform
 * TEE Client API Specification
 */
#ifndef   __TEE_CLIENT_API_H__
#define   __TEE_CLIENT_API_H__

#if (!defined(TEEC_EXPORT)) && defined(__cplusplus)
#define TEEC_EXPORT       extern "C"
#else
#define TEEC_EXPORT
#endif // __cplusplus

#include "tee_client_api_ext.h"
#include "tee_client_types.h"
#include "tee_client_error.h"

#if TBASE_API_LEVEL >= 3
#include "tee_client_api_imp.h"

/* The header tee_client_api_imp.h must define implementation-dependent
   types, constants and macros.

   The implementation-dependent types are:
     - TEEC_Context_IMP
     - TEEC_Session_IMP
     - TEEC_SharedMemory_IMP
     - TEEC_Operation_IMP

   The implementation-dependent constants are:
     - TEEC_CONFIG_SHAREDMEM_MAX_SIZE
   The implementation-dependent macros are:
     - TEEC_PARAM_TYPES
*/

typedef struct {
    uint32_t   a;
    uint32_t   b;
} TEEC_Value;

/* Type definitions */
typedef struct TEEC_Context {
    TEEC_Context_IMP imp;
} TEEC_Context;

typedef struct TEEC_Session {
    TEEC_Session_IMP imp;
} TEEC_Session;

typedef struct TEEC_SharedMemory {
    union {
        void                *buffer;
        int                 fd;
    };
    size_t                  size;
    uint32_t                flags;
    TEEC_SharedMemory_IMP   imp;
} TEEC_SharedMemory;

typedef struct {
    void    *buffer;
    size_t  size;
} TEEC_TempMemoryReference;

typedef struct {
    TEEC_SharedMemory *parent;
    size_t  size;
    size_t  offset;
} TEEC_RegisteredMemoryReference;

typedef union {
    TEEC_TempMemoryReference        tmpref;
    TEEC_RegisteredMemoryReference  memref;
    TEEC_Value                      value;
} TEEC_Parameter;

typedef struct TEEC_Operation {
    uint32_t            started;
    uint32_t            paramTypes;
    TEEC_Parameter      params[4];
    TEEC_Operation_IMP  imp;
} TEEC_Operation;

#define TEEC_ORIGIN_API                     0x00000001
#define TEEC_ORIGIN_COMMS                   0x00000002
#define TEEC_ORIGIN_TEE                     0x00000003
#define TEEC_ORIGIN_TRUSTED_APP             0x00000004

#define TEEC_MEM_INPUT                      0x00000001
#define TEEC_MEM_OUTPUT                     0x00000002
#define TEEC_MEM_ION                        0x01000000

#define TEEC_NONE                           0x0
#define TEEC_VALUE_INPUT                    0x1
#define TEEC_VALUE_OUTPUT                   0x2
#define TEEC_VALUE_INOUT                    0x3
#define TEEC_MEMREF_TEMP_INPUT              0x5
#define TEEC_MEMREF_TEMP_OUTPUT             0x6
#define TEEC_MEMREF_TEMP_INOUT              0x7
#define TEEC_MEMREF_WHOLE                   0xC
#define TEEC_MEMREF_PARTIAL_INPUT           0xD
#define TEEC_MEMREF_PARTIAL_OUTPUT          0xE
#define TEEC_MEMREF_PARTIAL_INOUT           0xF

#define TEEC_LOGIN_PUBLIC                   0x00000000
#define TEEC_LOGIN_USER                     0x00000001
#define TEEC_LOGIN_GROUP                    0x00000002
#define TEEC_LOGIN_APPLICATION              0x00000004
#define TEEC_LOGIN_USER_APPLICATION         0x00000005
#define TEEC_LOGIN_GROUP_APPLICATION        0x00000006

#define TEEC_TIMEOUT_INFINITE               0xFFFFFFFF

#pragma GCC visibility push(default)

TEEC_EXPORT TEEC_Result TEEC_InitializeContext(
    const char   *name,
    TEEC_Context *context);

TEEC_EXPORT void  TEEC_FinalizeContext(
    TEEC_Context *context);

TEEC_EXPORT TEEC_Result  TEEC_RegisterSharedMemory(
    TEEC_Context      *context,
    TEEC_SharedMemory *sharedMem);

TEEC_EXPORT TEEC_Result  TEEC_AllocateSharedMemory(
    TEEC_Context      *context,
    TEEC_SharedMemory *sharedMem);

TEEC_EXPORT void  TEEC_ReleaseSharedMemory (
    TEEC_SharedMemory *sharedMem);

TEEC_EXPORT TEEC_Result  TEEC_OpenSession (
    TEEC_Context    *context,
    TEEC_Session    *session,
    const TEEC_UUID *destination,
    uint32_t        connectionMethod,
    const void      *connectionData,
    TEEC_Operation  *operation,
    uint32_t        *returnOrigin);

TEEC_EXPORT void  TEEC_CloseSession (
    TEEC_Session *session);

TEEC_EXPORT TEEC_Result TEEC_InvokeCommand(
    TEEC_Session     *session,
    uint32_t         commandID,
    TEEC_Operation   *operation,
    uint32_t         *returnOrigin);

TEEC_EXPORT void  TEEC_RequestCancellation(
    TEEC_Operation *operation);

#pragma GCC visibility pop

#endif /* TBASE_API_LEVEL */

#endif /* __TEE_CLIENT_API_H__ */
