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

#ifndef _CFG_BWCS_D_H
#define _CFG_BWCS_D_H
#include "inc/bwcs_custom.h"
ap_nvram_bwcs_config_struct stBWCSConfigDefault =
{
    /* Real Time RSSI Threshold : BT / WIFI1 / WIFI2 */
    {RT_RSSI_TH_BT, RT_RSSI_TH_WIFI1, RT_RSSI_TH_WIFI2}
    ,
    /* Non Real Time RSSI Threshold : BT / WIFI1 / WIFI2 */
    {NRT_RSSI_TH_BT, NRT_RSSI_TH_WIFI1, NRT_RSSI_TH_WIFI2}
    ,
    /* Antenna path compensation */
    ANT_PATH_COMP
    ,
    /* antenna path switch protection period, Unit is seconds */
    ANT_SWITCH_PROT_TIME
    ,
    /* TX Flow control : medium time / period time */
    WIFI_TX_FLOW_CTRL
    ,
    /* BT RX Range : Low / High */
    BT_RX_RANGE
    ,
    /* BT TX power : WIFI OFF / WIFI SCO / WIFI ACL */
    {BT_TX_PWR_WIFI_OFF, BT_TX_PWR_SCO, BT_TX_PWR_ACL}
    ,
    /* Reserved                     ,  5 */
    RESERVED
};
#endif /* _CFG_BWCS_D_H */
