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

#ifndef MTK_WPA_SUPPLICANT_HIDL_SUPPLICANT_H
#define MTK_WPA_SUPPLICANT_HIDL_SUPPLICANT_H

#include <android-base/macros.h>

#include <android/hardware/wifi/supplicant/1.0/types.h>
#include <vendor/mediatek/hardware/wifi/supplicant/2.0/ISupplicant.h>
#include <vendor/mediatek/hardware/wifi/supplicant/2.0/ISupplicantCallback.h>
#include <vendor/mediatek/hardware/wifi/supplicant/2.0/ISupplicantIface.h>

extern "C" {
#include "utils/common.h"
#include "utils/includes.h"
#include "utils/wpa_debug.h"
#include "wpa_supplicant_i.h"
}

using android::hardware::wifi::supplicant::V1_0::SupplicantStatus;
using android::hardware::wifi::supplicant::V1_0::SupplicantStatusCode;

namespace vendor {
namespace mediatek {
namespace hardware {
namespace wifi {
namespace supplicant {
namespace V2_1 {
namespace implementation {
using android::sp;
using android::hardware::Return;
using android::hardware::wifi::supplicant::V1_0::SupplicantStatus;
using namespace vendor::mediatek::hardware::wifi::supplicant::V2_0;

/**
 * Implementation of the supplicant hidl object. This hidl
 * object is used core for global control operations on
 * wpa_supplicant.
 */
class Supplicant : public ISupplicant
{
public:
    Supplicant(struct wpa_global* global);
    ~Supplicant() override = default;
    bool isValid();

    // Hidl methods exposed.
    Return<void> getInterface(
        const android::hardware::wifi::supplicant::V1_0::ISupplicant::IfaceInfo& iface_info,
        getInterface_cb _hidl_cb) override;
    Return<void> registerCallback(
        const sp<ISupplicantCallback>& callback,
        registerCallback_cb _hidl_cb) override;

private:
    // Corresponding worker functions for the HIDL methods.
    std::pair<SupplicantStatus, sp<ISupplicantIface>> getInterfaceInternal(
        const android::hardware::wifi::supplicant::V1_0::ISupplicant::IfaceInfo& iface_info);
    SupplicantStatus registerCallbackInternal(
        const sp<ISupplicantCallback>& callback);

    // Raw pointer to the global structure maintained by the core.
    struct wpa_global* wpa_global_;

    DISALLOW_COPY_AND_ASSIGN(Supplicant);
};

}  // namespace implementation
}  // namespace V2_1
}  // namespace wifi
}  // namespace supplicant
}  // namespace hardware
}  // namespace mediatek
}  //namespace vendor
#endif  // MTK_WPA_SUPPLICANT_HIDL_SUPPLICANT_H
