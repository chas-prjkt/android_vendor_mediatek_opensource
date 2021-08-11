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

/* Common open/file device functions for Mobicore and GP */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>

#include "iclient.h"

class Common: public trustonic::IClient {
    struct Impl;
    const std::unique_ptr<Impl> pimpl_;
    Common();
public:
    ~Common() override;

    // Proprietary
    void TEEC_TT_RegisterPlatformContext(
        void*                   globalContext,
        void*                   localContext) override;

    TEEC_Result TEEC_TT_TestEntry(
        void*                   buff,
        size_t                  len,
        uint32_t*               tag) override;

    // Global Platform
    TEEC_Result TEEC_InitializeContext(
        const char*             name,
        TEEC_Context*           context) override;

    void TEEC_FinalizeContext(
        TEEC_Context*           context) override;

    TEEC_Result TEEC_RegisterSharedMemory(
        TEEC_Context*           context,
        TEEC_SharedMemory*      sharedMem) override;

    TEEC_Result TEEC_AllocateSharedMemory(
        TEEC_Context*           context,
        TEEC_SharedMemory*      sharedMem) override;

    void TEEC_ReleaseSharedMemory(
        TEEC_SharedMemory*      sharedMem) override;

    TEEC_Result TEEC_OpenSession(
        TEEC_Context*           context,
        TEEC_Session*           session,
        const TEEC_UUID*        destination,
        uint32_t                connectionMethod,
        const void*             connectionData,
        TEEC_Operation*         operation,
        uint32_t*               returnOrigin) override;

    void TEEC_CloseSession(
        TEEC_Session*           session) override;

    TEEC_Result TEEC_InvokeCommand(
        TEEC_Session*           session,
        uint32_t                commandID,
        TEEC_Operation*         operation,
        uint32_t*               returnOrigin) override;

    void TEEC_RequestCancellation(
        TEEC_Operation*         operation) override;

    // MobiCore
    mcResult_t mcOpenDevice(
        uint32_t                deviceId) override;

    mcResult_t mcCloseDevice(
        uint32_t                deviceId) override;

    mcResult_t mcOpenSession(
        mcSessionHandle_t*      session,
        const mcUuid_t*         uuid,
        uint8_t*                tci,
        uint32_t                tciLen) override;

    mcResult_t mcOpenTrustlet(
        mcSessionHandle_t*      session,
        mcSpid_t                spid,
        uint8_t*                trustedapp,
        uint32_t                tLen,
        uint8_t*                tci,
        uint32_t                tciLen) override;

    mcResult_t mcCloseSession(
        mcSessionHandle_t*      session) override;

    mcResult_t mcNotify(
        mcSessionHandle_t*      session) override;

    mcResult_t mcWaitNotification(
        mcSessionHandle_t*      session,
        int32_t                 timeout) override;

    mcResult_t mcMallocWsm(
        uint32_t                deviceId,
        uint32_t                len,
        uint8_t**               wsm) override;

    mcResult_t mcFreeWsm(
        uint32_t                deviceId,
        uint8_t*                wsm,
        uint32_t                len) override;

    mcResult_t mcMap(
        mcSessionHandle_t*      session,
        void*                   buf,
        uint32_t                len,
        mcBulkMap_t*            mapInfo) override;

    mcResult_t mcUnmap(
        mcSessionHandle_t*      session,
        void*                   buf,
        mcBulkMap_t*            mapInfo) override;

    mcResult_t mcGetSessionErrorCode(
        mcSessionHandle_t*      session,
        int32_t*                lastErr) override;

    mcResult_t mcGetMobiCoreVersion(
        uint32_t                deviceId,
        mcVersionInfo_t*        versionInfo) override;

    // Singleton
    static Common& getInstance() {
        static Common client;
        return client;
    }
};

#endif // __COMMON_H__
