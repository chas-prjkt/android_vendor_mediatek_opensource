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

extern "C" {
#include "mtk_hidl.h"
#include "utils/common.h"
#include "utils/includes.h"
}

using vendor::mediatek::hardware::wifi::supplicant::V2_1::implementation::HidlManager;

void mtk_wpas_hidl_init(struct wpa_global *global)
{
    HidlManager *hidl_manager;

    hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return;
    hidl_manager->registerHidlService(global);
}

void mtk_wpas_hidl_deinit()
{
    HidlManager::destroyInstance();
}

int mtk_wpas_hidl_register_interface(struct wpa_supplicant *wpa_s)
{
    if (!wpa_s)
        return 1;

    wpa_printf(
        MSG_DEBUG, "Registering interface to mtk hidl control: %s",
        wpa_s->ifname);

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return 1;

    return hidl_manager->registerInterface(wpa_s);
}

int mtk_wpas_hidl_unregister_interface(struct wpa_supplicant *wpa_s)
{
    if (!wpa_s)
        return 1;

    wpa_printf(
        MSG_DEBUG, "Deregistering interface from mtk hidl control: %s",
        wpa_s->ifname);

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return 1;

    return hidl_manager->unregisterInterface(wpa_s);
}

int mtk_wpas_hidl_register_network(
    struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
    if (!wpa_s || !ssid)
        return 1;

    wpa_printf(
        MSG_DEBUG, "Registering network to mtk hidl control: %d", ssid->id);

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return 1;

    return hidl_manager->registerNetwork(wpa_s, ssid);
}

int mtk_wpas_hidl_unregister_network(
    struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
    if (!wpa_s || !ssid)
        return 1;

    wpa_printf(
        MSG_DEBUG, "Deregistering network from mtk hidl control: %d", ssid->id);

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return 1;

    return hidl_manager->unregisterNetwork(wpa_s, ssid);
}

void mtk_wpas_hidl_notify_wnm_ess_disassoc_imminent_notice(
    struct wpa_supplicant *wpa_s, u32 pmf_enabled, u32 reauth_delay, const char *url)
{
    if (!wpa_s || !url)
        return;

    wpa_printf(
        MSG_DEBUG,
        "Notifying WNM ESS disassoc imminent notice rx to hidl control: %s",
        url);

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return;

    hidl_manager->notifyWNMRxEssDisassocImminentNotice(
        wpa_s, pmf_enabled, reauth_delay, url);
}

void mtk_wpas_hidl_notify_data_stall_reason(struct wpa_supplicant *wpa_s, uint32_t reason)
{
    if (!wpa_s)
        return;

    wpa_printf(MSG_DEBUG, "Notifying data stall to hidl control");

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return;

    hidl_manager->notifyDataStallReason(wpa_s, reason);
}

void mtk_wpas_hidl_notify_assoc_freq_changed(struct wpa_supplicant *wpa_s)
{
    if (!wpa_s)
        return;

    wpa_printf(MSG_DEBUG, "Notifying associated frequency changed to hidl control: %d",
        wpa_s->assoc_freq);

    HidlManager *hidl_manager = HidlManager::getInstance();
    if (!hidl_manager)
        return;

    hidl_manager->notifyAssocFreqChanged(wpa_s);
}
