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

#ifndef WV_DHDCP_EXT_H_
#define WV_DHDCP_EXT_H_

/**
 * Copy define from OEMCryptoCENC.h which will be used by SRM, need upgrade when changed
 */
#define OEMCrypto_SUCCESS                  0
#define OEMCrypto_ERROR_NOT_IMPLEMENTED   25
#define OEMCrypto_ERROR_UNKNOWN_FAILURE   28
#define OEMCrypto_ERROR_INVALID_CONTEXT   29
#define OEMCrypto_ERROR_SIGNATURE_FAILURE 30
#define OEMCrypto_ERROR_BUFFER_TOO_LARGE  39

#ifdef __cplusplus
extern "C"
{
#endif

bool WvHdcpExt_IsSRMUpdateSupported();
uint32_t WvHdcpExt_GetCurrentSRMVersion(uint16_t* version);
uint32_t WvHdcpExt_LoadSRM(const uint8_t* buffer, size_t buffer_length);
uint32_t WvHdcpExt_RemoveSRM();

#ifdef __cplusplus
}
#endif

#endif // WV_DHDCP_EXT_H_
