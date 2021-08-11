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
 * This header file defines the implementation-dependent types,
 * constants and macros for all the Kinibi implementations of the TEE Client API
 */
#ifndef   __TEE_CLIENT_API_IMP_H__
#define   __TEE_CLIENT_API_IMP_H__

#if TBASE_API_LEVEL >= 3

#include <pthread.h>

#define TEEC_MEM_INOUT (TEEC_MEM_INPUT | TEEC_MEM_OUTPUT)
#define TEEC_MEM_FLAGS_MASK (TEEC_MEM_ION | TEEC_MEM_INPUT | TEEC_MEM_OUTPUT)

typedef struct {
    uint32_t                    open_mode;
} TEEC_Context_IMP;

typedef struct {
    uint32_t                    sessionId;
    TEEC_Context_IMP            reserved1;
    void                        *reserved2_tci; // TCI used in tests for old versions
    bool                        reserved3;
    pthread_mutex_t             reserved4;
} TEEC_Session_IMP;

typedef struct {
    bool                        reserved;
} TEEC_SharedMemory_IMP;

typedef struct {
    void                        *reserved;
} TEEC_Operation_IMP;

#define TEEC_PARAM_TYPES(entry0Type, entry1Type, entry2Type, entry3Type) \
   ((entry0Type) | ((entry1Type) << 4) | ((entry2Type) << 8) | ((entry3Type) << 12))

#endif /* TBASE_API_LEVEL >= 3 */

#if TBASE_API_LEVEL >= 9

#pragma GCC visibility push(default)

/*
 * Internal use only
 */
TEEC_EXPORT TEEC_Result TEEC_TT_TestEntry(
    void*                   buff,
    size_t                  len,
    uint32_t*               tag);

#pragma GCC visibility pop

#endif /* TBASE_API_LEVEL >= 9 */

#endif /* __TEE_CLIENT_API_IMP_H__ */
