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

#define LOG_TAG "mtk_ifc"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <log/log.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/sockios.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <ifcutils/ifc.h>


#define SIOCSTXQSTATE (SIOCDEVPRIVATE + 0)  //start/stop ccmni tx queue
#define SIOCSCCMNICFG (SIOCDEVPRIVATE + 1)  //configure ccmni/md remapping
#define SIOCACKPRIO  (SIOCDEVPRIVATE + 3)  //disable ack first mechanism

int ifc_set_txq_state(const char *ifname, int state)
{
    struct ifreq ifr;
    int ret, ctl_sock;

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    ifr.ifr_ifru.ifru_ivalue = state;

    ctl_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ctl_sock < 0){
	   ALOGE("create ctl socket failed\n");
       return -1;
    }
    ret = ioctl(ctl_sock, SIOCSTXQSTATE, &ifr);
    if(ret < 0)
       ALOGE("ifc_set_txq_state failed, err:%d(%s)\n", errno, strerror(errno));
    else
       ALOGI("ifc_set_txq_state as %d, ret: %d\n", state, ret);

    close(ctl_sock);

    return ret;
}

int ifc_ccmni_md_cfg(const char *ifname, int md_id)
{
    struct ifreq ifr;
    int ret = 0;
    int ctl_sock = 0;

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    ifr.ifr_ifru.ifru_ivalue = md_id;

    ctl_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ctl_sock < 0){
        ALOGE("ifc_ccmni_md_cfg: create ctl socket failed\n");
        return -1;
    }

    if(ioctl(ctl_sock, SIOCSCCMNICFG, &ifr) < 0) {
        ALOGE("ifc_ccmni_md_configure(ifname=%s, md_id=%d) error:%d(%s)", \
             ifname, md_id, errno, strerror(errno));
       ret = -1;
    } else {
        ALOGI("ifc_ccmni_md_configure(ifname=%s, md_id=%d) OK", ifname, md_id);
    }

    close(ctl_sock);
    return ret;
}


int ifc_enable_ack_prio(int enable)
{
    struct ifreq ifr;
    int ret, ctl_sock;

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, "ccmni0", IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    ifr.ifr_ifru.ifru_ivalue = enable;

    ctl_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ctl_sock < 0){
        ALOGE("create ctl socket failed\n");
       return -1;
    }
    ret = ioctl(ctl_sock, SIOCACKPRIO, &ifr);
    if(ret < 0)
       ALOGE("ifc_set_ack_prio failed, err:%d(%s)\n", errno, strerror(errno));
    else
       ALOGI("ifc_set_ack_prio as %d, ret: %d\n", enable, ret);

    close(ctl_sock);

    return ret;
}
