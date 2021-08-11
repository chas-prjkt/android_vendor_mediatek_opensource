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

#ifndef __TEE_CLIENT_INTERFACE_H__
#define __TEE_CLIENT_INTERFACE_H__

#include <memory>
#include <string>
#include <tuple>

#include "MobiCoreDriverApi.h"
#include "tee_client_api.h"

// Debug macros
#define ENTER() \
    do { \
        LOG_D("entering %s", __func__); \
    } while (0)

#define EXIT_NORETURN() \
    do { \
        LOG_D("exiting %s", __func__); \
        return; \
    } while (0)

#define EXIT(a__) \
    do { \
        auto rc__ = (a__); \
        LOG_D("exiting %s rc 0x%x", __func__, rc__); \
        return rc__; \
    } while (0)

namespace trustonic {

class IClient {
public:
    virtual ~IClient() {}

    // Proprietary
    virtual void TEEC_TT_RegisterPlatformContext(
        void*                   globalContext,
        void*                   localContext) = 0;

    virtual TEEC_Result TEEC_TT_TestEntry(
        void*                   buff,
        size_t                  len,
        uint32_t*               tag) = 0;

    // Global Platform
    virtual TEEC_Result TEEC_InitializeContext(
        const char*             name,
        TEEC_Context*           context) = 0;

    virtual void TEEC_FinalizeContext(
        TEEC_Context*           context) = 0;

    virtual TEEC_Result TEEC_RegisterSharedMemory(
        TEEC_Context*           context,
        TEEC_SharedMemory*      sharedMem) = 0;

    virtual TEEC_Result TEEC_AllocateSharedMemory(
        TEEC_Context*           context,
        TEEC_SharedMemory*      sharedMem) = 0;

    virtual void TEEC_ReleaseSharedMemory(
        TEEC_SharedMemory*      sharedMem) = 0;

    virtual TEEC_Result TEEC_OpenSession(
        TEEC_Context*           context,
        TEEC_Session*           session,
        const TEEC_UUID*        destination,
        uint32_t                connectionMethod,
        const void*             connectionData,
        TEEC_Operation*         operation,
        uint32_t*               returnOrigin) = 0;

    virtual void TEEC_CloseSession(
        TEEC_Session*           session) = 0;

    virtual TEEC_Result TEEC_InvokeCommand(
        TEEC_Session*           session,
        uint32_t                commandID,
        TEEC_Operation*         operation,
        uint32_t*               returnOrigin) = 0;

    virtual void TEEC_RequestCancellation(
        TEEC_Operation*         operation) = 0;

    // MobiCore
    virtual mcResult_t mcOpenDevice(
        uint32_t                deviceId) = 0;

    virtual mcResult_t mcCloseDevice(
        uint32_t                deviceId) = 0;

    virtual mcResult_t mcOpenSession(
        mcSessionHandle_t*      session,
        const mcUuid_t*         uuid,
        uint8_t*                tci,
        uint32_t                tciLen) = 0;

    virtual mcResult_t mcOpenTrustlet(
        mcSessionHandle_t*      session,
        mcSpid_t                spid,
        uint8_t*                trustedapp,
        uint32_t                tLen,
        uint8_t*                tci,
        uint32_t                tciLen) = 0;

    virtual mcResult_t mcCloseSession(
        mcSessionHandle_t*      session) = 0;

    virtual mcResult_t mcNotify(
        mcSessionHandle_t*      session) = 0;

    virtual mcResult_t mcWaitNotification(
        mcSessionHandle_t*      session,
        int32_t                 timeout) = 0;

    virtual mcResult_t mcMallocWsm(
        uint32_t                deviceId,
        uint32_t                len,
        uint8_t**               wsm) = 0;

    virtual mcResult_t mcFreeWsm(
        uint32_t                deviceId,
        uint8_t*                wsm,
        uint32_t                len) = 0;

    virtual mcResult_t mcMap(
        mcSessionHandle_t*      session,
        void*                   buf,
        uint32_t                len,
        mcBulkMap_t*            mapInfo) = 0;

    virtual mcResult_t mcUnmap(
        mcSessionHandle_t*      session,
        void*                   buf,
        mcBulkMap_t*            mapInfo) = 0;

    virtual mcResult_t mcGetSessionErrorCode(
        mcSessionHandle_t*      session,
        int32_t*                lastErr) = 0;

    virtual mcResult_t mcGetMobiCoreVersion(
        uint32_t                deviceId,
        mcVersionInfo_t*        versionInfo) = 0;

    // Specific
    struct BindInformation {
        char package_name[128];
        char starter_class[32];
    };

    virtual bool getBindInformation(BindInformation* /*bind_information*/) {
        return false;
    }
};

}

#endif // __TEE_CLIENT_INTERFACE_H__
