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

#ifndef MTK_HIDL_UTILS_H
#define MTK_HIDL_UTILS_H

#ifdef CONFIG_CTRL_IFACE_MTK_HIDL
#include <vendor/mediatek/hardware/wifi/supplicant/2.0/ISupplicantStaNetwork.h>
#define MTK_ALLOWED_KEY_MGMT                                           \
    static_cast<uint32_t>(vendor::mediatek::hardware::wifi::supplicant \
    ::V2_0::ISupplicantStaNetwork::KeyMgmtMask::WPA_EAP_SHA256) |      \
    static_cast<uint32_t>(vendor::mediatek::hardware::wifi::supplicant \
    ::V2_0::ISupplicantStaNetwork::KeyMgmtMask::WAPI_PSK) |            \
    static_cast<uint32_t>(vendor::mediatek::hardware::wifi::supplicant \
    ::V2_0::ISupplicantStaNetwork::KeyMgmtMask::WAPI_CERT)

#define MTK_ALLOWED_PROTO_MASK                                         \
    static_cast<uint32_t>(vendor::mediatek::hardware::wifi::supplicant \
    ::V2_0::ISupplicantStaNetwork::ProtoMask::WAPI)

#define MTK_ALLOWED_GROUP_CIPHER_MASK                                  \
    static_cast<uint32_t>(vendor::mediatek::hardware::wifi::supplicant \
    ::V2_0::ISupplicantStaNetwork::GroupCipherMask::SM4)

#define MTK_ALLOWED_PAIRWISE_CIPHER_MASK                               \
    static_cast<uint32_t>(vendor::mediatek::hardware::wifi::supplicant \
    ::V2_0::ISupplicantStaNetwork::PairwiseCipherMask::SM4)
#else
#define MTK_ALLOWED_KEY_MGMT
#define MTK_ALLOWED_PROTO_MASK
#define MTK_ALLOWED_GROUP_CIPHER_MASK
#define MTK_ALLOWED_PAIRWISE_CIPHER_MASK
#endif

#endif /* MTK_HIDL_UTILS_H */
