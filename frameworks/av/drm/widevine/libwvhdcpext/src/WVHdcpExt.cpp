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

//#define LOG_NDEBUG 0
#define LOG_TAG "WVHdcpExt"
#include <utils/Log.h>

#include "WVHdcpExt.h"

bool WvHdcpExt_IsSRMUpdateSupported() {
    // If you implement SRM update for HDCP feature, please return true
    return false;
}

uint32_t WvHdcpExt_GetCurrentSRMVersion(uint16_t* version) {
    // If you implement SRM update for HDCP feature, please return OEMCrypto_SUCCESS.
    // Based on the considerations of security, we will not return SRM version returned by this
    // function, we need you set SRM version to MTK DRM HDCP T-driver by you HDCP TA(we will
    // provide how to do this in guide document), and widevine TA will get the SRM version from
    // the T-driver, then use it to check or return to app.
    //   So please set SRM version to T-driver when this function has been called.
    return OEMCrypto_ERROR_NOT_IMPLEMENTED;
}

uint32_t WvHdcpExt_LoadSRM(const uint8_t* buffer, size_t buffer_length) {
    // If you implement SRM update for HDCP feature, please return below value case by case, default
    // we return OEMCrypto_ERROR_NOT_IMPLEMENTED:
    // OEMCrypto_SUCCESS - if the file was valid and was installed.
    // OEMCrypto_ERROR_INVALID_CONTEXT - if the SRM version is too low, or the file is corrupted.
    // OEMCrypto_ERROR_SIGNATURE_FAILURE - If the signature is invalid.
    // OEMCrypto_ERROR_BUFFER_TOO_LARGE - if the buffer is too large for the device.
    // OEMCrypto_ERROR_NOT_IMPLEMENTED - default
    return OEMCrypto_ERROR_NOT_IMPLEMENTED;
}

uint32_t WvHdcpExt_RemoveSRM() {
    // This function should not be implemented on production devices, and will only be used to
    // verify unit tests on a test device.
    return OEMCrypto_ERROR_NOT_IMPLEMENTED;
}
