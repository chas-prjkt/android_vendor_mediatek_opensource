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

#ifndef MTK_WPA_SUPPLICANT_HIDL_IFACE_CONFIG_UTILS_H
#define MTK_WPA_SUPPLICANT_HIDL_IFACE_CONFIG_UTILS_H

#include <android-base/macros.h>

extern "C" {
#include "utils/common.h"
#include "utils/includes.h"
#include "wpa_supplicant_i.h"
#include "config.h"
}

/**
 * Utility functions to set various config parameters of an iface via HIDL
 * methods.
 */
namespace vendor {
namespace mediatek {
namespace hardware {
namespace wifi {
namespace supplicant {
namespace V2_1 {
namespace implementation {
namespace iface_config_utils {

SupplicantStatus setWapiCertList(
    struct wpa_supplicant* wpa_s, const std::string& list);
}  // namespace iface_config_utils
}  // namespace implementation
}  // namespace V2_1
}  // namespace wifi
}  // namespace supplicant
}  // namespace hardware
}  // namespace mediatek
}  //namespace vendor
#endif  // MTK_WPA_SUPPLICANT_HIDL_IFACE_CONFIG_UTILS_H
