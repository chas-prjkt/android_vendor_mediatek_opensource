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

#include "hidl_manager.h"
#include "hidl/1.3/hidl_return_util.h"
#include "supplicant.h"

namespace vendor {
namespace mediatek {
namespace hardware {
namespace wifi {
namespace supplicant {
namespace V2_1 {
namespace implementation {
using android::hardware::wifi::supplicant::V1_3::implementation::hidl_return_util::validateAndCall;
using android::hardware::wifi::supplicant::V1_0::SupplicantStatus;
using android::hardware::wifi::supplicant::V1_0::SupplicantStatusCode;

Supplicant::Supplicant(struct wpa_global* global) : wpa_global_(global) {}
bool Supplicant::isValid()
{
    // This top level object cannot be invalidated.
    return true;
}

Return<void> Supplicant::getInterface(
    const android::hardware::wifi::supplicant::V1_0::ISupplicant::IfaceInfo& iface_info, getInterface_cb _hidl_cb)
{
    return validateAndCall(
        this, SupplicantStatusCode::FAILURE_IFACE_INVALID,
        &Supplicant::getInterfaceInternal, _hidl_cb, iface_info);
}

Return<void> Supplicant::registerCallback(
    const sp<ISupplicantCallback>& callback, registerCallback_cb _hidl_cb)
{
    return validateAndCall(
        this, SupplicantStatusCode::FAILURE_IFACE_INVALID,
        &Supplicant::registerCallbackInternal, _hidl_cb, callback);
}

std::pair<SupplicantStatus, sp<ISupplicantIface>>
Supplicant::getInterfaceInternal(const android::hardware::wifi::supplicant::V1_0::ISupplicant::IfaceInfo& iface_info)
{
    struct wpa_supplicant* wpa_s =
        wpa_supplicant_get_iface(wpa_global_, iface_info.name.c_str());
    if (!wpa_s) {
        return {{SupplicantStatusCode::FAILURE_IFACE_UNKNOWN, ""},
            nullptr};
    }
    HidlManager* hidl_manager = HidlManager::getInstance();
#if CONFIG_P2P_HIDL
    if (iface_info.type == IfaceType::P2P) {
        android::sp<ISupplicantP2pIface> iface;
        if (!hidl_manager ||
            hidl_manager->getP2pIfaceHidlObjectByIfname(
            wpa_s->ifname, &iface)) {
            return {{SupplicantStatusCode::FAILURE_UNKNOWN, ""},
                iface};
        }
        // Set this flag true here, since there is no HIDL initialize method for the p2p
        // config, and the supplicant interface is not ready when the p2p iface is created.
        wpa_s->conf->persistent_reconnect = true;
        return {{SupplicantStatusCode::SUCCESS, ""}, iface};
    } else {
#endif
        android::sp<ISupplicantStaIface> iface;
        if (!hidl_manager ||
            hidl_manager->getStaIfaceHidlObjectByIfname(
            wpa_s->ifname, &iface)) {
            return {{SupplicantStatusCode::FAILURE_UNKNOWN, ""},
                iface};
        }
        return {{SupplicantStatusCode::SUCCESS, ""}, iface};
#if CONFIG_P2P_HIDL
    }
#endif
}

SupplicantStatus Supplicant::registerCallbackInternal(
    const sp<ISupplicantCallback>& callback)
{
    HidlManager* hidl_manager = HidlManager::getInstance();
    if (!hidl_manager ||
        hidl_manager->addSupplicantCallbackHidlObject(callback)) {
        return {SupplicantStatusCode::FAILURE_UNKNOWN, ""};
    }
    return {SupplicantStatusCode::SUCCESS, ""};
}
}  // namespace implementation
}  // namespace V2_1
}  // namespace wifi
}  // namespace supplicant
}  // namespace hardware
}  //namespace mediatek
}  // namespace vendor
