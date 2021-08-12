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

#include "l2_packet/l2_packet.h"

#define WLAN_EID_WAPI 68

struct wapi_context {
    struct l2_packet_data *l2_wai;
    u8 bss_wapi_ie[64];
    u8 bss_wapi_ie_len;
};

/* struct */
typedef enum
{
    /* No WAPI */
    AUTH_TYPE_NONE_WAPI = 0,
    /* Certificate */
    AUTH_TYPE_WAPI_CERT,
    /* Pre-PSK */
    AUTH_TYPE_WAPI_PSK,
}AUTH_TYPE;

typedef enum
{
    /* ascii */
    KEY_TYPE_ASCII = 0,
    /* HEX */
    KEY_TYPE_HEX,
}KEY_TYPE;

typedef struct
{
    /* Authentication type */
    AUTH_TYPE authType;
    u8 reinit_cert_list;
    /* WAPI_CERT */
    char *cert_list;
    char *as_cert;
    char *asue_cert;
    /* WAPI_PSK Key type */
    KEY_TYPE kt;
    /* Key length */
    unsigned int kl;
    /* Key value */
    unsigned char kv[128];
}CNTAP_PARA;

typedef enum
{
    WAPI_AUTH_ERR,
    WAPI_ERR_NUM
} WAPI_LIB_ERR_CLASS;

typedef enum
{
    CONN_ASSOC = 0,
    CONN_DISASSOC,
}CONN_STATUS;

typedef struct
{
    unsigned char v[6];
    unsigned char pad[2];
}MAC_ADDRESS;

typedef void (*timeout_handler)(void *eloop_data, void *user_ctx);

struct wapi_cb_ctx {
    void *ctx; /* pointer to arbitrary upper level context */
    int mtu_len;

    /*face to mt592x*/
    int (*msg_send)(void *priv, const u8 *msg_in, int msg_in_len,
                             u8 *msg_out, int *msg_out_len);

    /*send output to wpa_ctrl*/
    void (*wpa_msg)(void *ctx, int level, const char *fmt, ...);

    void (*wapi_error)(void *ctx, int class, const char *fmt, ...);

    /*set wapi key*/
    int (*set_key)(void *ctx, int alg,
               const u8 *addr, int key_idx, int set_tx,
               const u8 *seq, size_t seq_len,
               const u8 *key, size_t key_len);

    /*send WAI frame*/
    int (*ether_send)(void *ctx, const u8* pbuf, int length);

    /*set wpa_supplicant state*/
    void (*set_state)(void *ctx, int state);

    /*get wpa_supplicant state*/
    int (*get_state)(void *ctx);

    /*send deauthenticateion*/
    void (*deauthenticate)(void *ctx, int reason_code);

    /*set one-shot timer*/
    int  (*set_timer)(unsigned int secs, unsigned int usecs,
               timeout_handler handler,
               void *eloop_data, void *user_data);

    /*clear one-shot timer*/
    int  (*cancel_timer)(timeout_handler handler,
             void *eloop_data, void *user_data);
};

int wapi_set_suites(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid,
            struct wpa_bss *bss, u8 *wpa_ie, size_t *wpa_ie_len);
int wapi_init_l2(struct wpa_supplicant *wpa_s);
void wapi_handle_cert_list_changed(struct wpa_supplicant *wpa_s);
void wapi_event_disassoc(struct wpa_supplicant *wpa_s, const u8 *bssid);
int wapi_init(struct wpa_supplicant *wpa_s);
int wapi_deinit(struct wpa_supplicant *wpa_s);
void wapi_event_assoc(struct wpa_supplicant *wpa_s);

/** APIs **/
void init_wapi_api();
unsigned long (* wapi_set_rx_wai)(const u8 *, int);
int (* wapi_lib_init)(struct wapi_cb_ctx *);
int (* wapi_lib_exit)();
int (* wapi_set_user)(const CNTAP_PARA *);
unsigned int (* wapi_get_assoc_ie)(unsigned char *);
void (* wapi_set_msg)(CONN_STATUS, const MAC_ADDRESS *, const MAC_ADDRESS *, unsigned char *, unsigned char);
