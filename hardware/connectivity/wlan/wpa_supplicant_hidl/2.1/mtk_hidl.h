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

#ifndef MTK_WPA_SUPPLICANT_HIDL_HIDL_H
#define MTK_WPA_SUPPLICANT_HIDL_HIDL_H

#ifdef _cplusplus
extern "C" {
#endif  // _cplusplus

/**
 * This is the hidl RPC interface entry point to the wpa_supplicant core.
 * This initializes the hidl driver & HidlManager instance and then forwards
 * all the notifcations from the supplicant core to the HidlManager.
 */
struct wpas_hidl_priv;
struct wpa_global;

#ifdef CONFIG_CTRL_IFACE_MTK_HIDL
void mtk_wpas_hidl_init(struct wpa_global *global);
void mtk_wpas_hidl_deinit();
int mtk_wpas_hidl_register_interface(struct wpa_supplicant *wpa_s);
int mtk_wpas_hidl_unregister_interface(struct wpa_supplicant *wpa_s);
int mtk_wpas_hidl_register_network(
    struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid);
int mtk_wpas_hidl_unregister_network(
    struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid);
void mtk_wpas_hidl_notify_wnm_ess_disassoc_imminent_notice(
    struct wpa_supplicant *wpa_s, u32 pmf_enabled, u32 reauth_delay, const char *url);
void mtk_wpas_hidl_notify_data_stall_reason(struct wpa_supplicant *wpa_s, uint32_t reason);
void mtk_wpas_hidl_notify_assoc_freq_changed(struct wpa_supplicant *wpa_s);
#else   // CONFIG_CTRL_IFACE_MTK_HIDL
static inline void mtk_wpas_hidl_init(struct wpa_global *global) {}
static inline void mtk_wpas_hidl_deinit() {}
static inline int mtk_wpas_hidl_register_interface(struct wpa_supplicant *wpa_s)
{
    return 0;
}
static inline int mtk_wpas_hidl_unregister_interface(struct wpa_supplicant *wpa_s)
{
    return 0;
}
static inline int mtk_wpas_hidl_register_network(
    struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
    return 0;
}
static inline int mtk_wpas_hidl_unregister_network(
    struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
    return 0;
}
static inline void mtk_wpas_hidl_notify_wnm_ess_disassoc_imminent_notice(
    struct wpa_supplicant *wpa_s, u32 pmf_enabled, u32 reauth_delay, const char *url)
{
}
static inline void mtk_wpas_hidl_notify_data_stall_reason(
    struct wpa_supplicant *wpa_s, uint32_t reason) {}
static void mtk_wpas_hidl_notify_assoc_freq_changed(struct wpa_supplicant *wpa_s) {}
#endif  // CONFIG_CTRL_IFACE_MTK_HIDL

#ifdef _cplusplus
}
#endif  // _cplusplus

#endif  // MTK_WPA_SUPPLICANT_HIDL_HIDL_H
