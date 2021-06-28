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
#define LOG_TAG "DrmCtaUtil"
#include <utils/Log.h>

#include <drm/drm_framework_common.h>

#include <DrmCtaUtil.h>
#include <DrmDef.h>
#include <utils/List.h>
#include <utils/String8.h>
#include <utils/threads.h>
#include <drm/DrmInfoEvent.h>
#include <drm/DrmMtkUtil.h>
#include <drm/DrmMtkDef.h>
#include <binder/IPCThreadState.h>

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


using namespace android;


String8 DrmCtaUtil::getPathFromFd(int fd)
{
    char buffer[256];
    char linkto[4096];
    memset(buffer, 0, 256);
    memset(linkto, 0, 4096);
    snprintf(buffer,sizeof(buffer), "/proc/%d/fd/%d", gettid(), fd);
    int len = 0;
    len = readlink(buffer, linkto, sizeof(linkto));
    if(len > 4096)
    {
        ALOGE("The file path is too long : %d", len);
        String8 path;
        return path;
    }
    return String8::format("%s",linkto);

}


uint32_t DrmCtaUtil::getNormalFromUintVar(String8 uvar)
{
    uint32_t value = 0;
    uint32_t len = uvar.length();
    uint32_t i = 0;
    uint8_t *str = (uint8_t *) uvar.string();
    while (i < len)
    {
        uint8_t c = str[i];
        printf("i = %u,c = 0x%x\n",i, c);
        value <<= 7;
        value |= (c & 0x7f);
        printf("value = 0x%x\n",value);
        if ((c & 0x80) == 0)
        {
            break;
        }
        ++i;
    }
    return value;
}

String8 DrmCtaUtil::getUintVarFromNormal(uint32_t normal)
{
    String8 str8;
    //printf("getUintVarFromNormal:normal-%x\n",normal);
    if (normal <= 0x0000007F)
    {
        //printf("One bytes\n");
        //Only one byte
        char c = (char) normal;
        str8.append(&c, 1);
    } else if (normal <= 0x00003FFF)
    {
        //printf("Two bytes\n");
        //Two bytes
        //Get the last 7 bits, and set continue bit to 0
        char lastByte = normal & 0x0000007F;

        char firstByte = (normal & 0x00003F80) >> 7;
        //set continue bit to 1
        firstByte = firstByte | 0x80;

        str8.append(&firstByte, 1);
        str8.append(&lastByte, 1);
    } else if (normal <= 0x001FFFFF)
    {
        //printf("Three bytes\n");
        //Three bytes
        //Get the last 7 bits, and set continue bit to 0
        char lastByte = normal & 0x0000007F;
        //printf("lastByte bytes:0x%x\n",lastByte);

        char middleByte = (normal & 0x00003F80) >> 7;
        //set continue bit to 1
        middleByte = middleByte | 0x80;
        //printf("middleByte bytes:0x%x\n",middleByte);

        char firstByte = normal >> 14;
        //set continue bit to 1
        firstByte = firstByte | 0x80;
        //printf("firstByte bytes:0x%x\n",firstByte);

        str8.append(&firstByte, 1);
        str8.append(&middleByte, 1);
        str8.append(&lastByte, 1);

    } else if (normal <= 0x0FFFFFFF)
    {
        //printf("Four bytes\n");
        //Four bytes
        //Get the last 7 bits, and set continue bit to 0
        char lastByte = normal & 0x0000007F;

        //Get the last second 7 bits, and set continue bit to 1
        char lastSecondByte = (normal & 0x00003F80) >> 7;
        //set continue bit to 1
        lastSecondByte = lastSecondByte | 0x80;

        //Get the last third 7 bits, and set continue bit to 1
        char lastThirdByte = (normal & 0x00003FC000) >> 14;
        //set continue bit to 1
        lastThirdByte = lastThirdByte | 0x80;

        char firstByte = normal >> 21;
        //set continue bit to 1
        firstByte = firstByte | 0x80;

        str8.append(&firstByte, 1);
        str8.append(&lastThirdByte, 1);
        str8.append(&lastSecondByte, 1);
        str8.append(&lastByte, 1);
    } else
    {
        //printf("Five bytes\n");
        //Five bytes
        //Get the last 7 bits, and set continue bit to 0
        char lastByte = normal & 0x0000007F;
        //printf("lastByte bytes:0x%x\n",lastByte);

        //Get the last second 7 bits, and set continue bit to 1
        char lastSecondByte = (normal & 0x00003F80) >> 7;
        //set continue bit to 1
        lastSecondByte = lastSecondByte | 0x80;
        //printf("lastSecondByte bytes:0x%x\n",lastSecondByte);

        //Get the last third 7 bits, and set continue bit to 1
        char lastThirdByte = (normal & 0x00003FC000) >> 14;
        //set continue bit to 1
        lastThirdByte = lastThirdByte | 0x80;
        //printf("lastThirdByte bytes:0x%x\n",lastThirdByte);

        //Get the last third 7 bits, and set continue bit to 1
        char lastFourthByte = (normal & 0x00003FE00000) >> 21;
        //set continue bit to 1
        lastFourthByte = lastThirdByte | 0x80;
        //printf("lastFourthByte bytes:0x%x\n",lastFourthByte);

        char firstByte = normal >> 28;
        //set continue bit to 1
        firstByte = firstByte | 0x80;
        //printf("firstByte bytes:0x%x\n",firstByte);

        str8.append(&firstByte, 1);
        str8.append(&lastFourthByte, 1);
        str8.append(&lastThirdByte, 1);
        str8.append(&lastSecondByte, 1);
        str8.append(&lastByte, 1);
    }
    return str8;
}

void testUintVarFunction()
{
    //Test one byte
    uint32_t normal = 0x7F;
    uint32_t result = 0;
    printf("Test One byte\n");
    String8 uvar8 = DrmCtaUtil::getUintVarFromNormal(normal);
    printf("#############\n");
    for (size_t i = 0; i < uvar8.size(); ++i)
    {
        printf("uvar8 = %0x\n", uvar8.string()[i]);
    }
    printf("#############\n");
    result = DrmCtaUtil::getNormalFromUintVar(uvar8);
    if (result != normal)
    {
        printf("FAIL - test one byte\n");
    }else
    {
        printf("SUCCESS - test one bytes\n");
    }
    printf("result = 0x%x\n", result);

    //Test Two bytes
    printf("Test Two byte\n");
    normal = 0x3FF0;
    uvar8 = DrmCtaUtil::getUintVarFromNormal(normal);
    printf("#############\n");
    for (size_t i = 0; i < uvar8.size(); ++i)
    {
        printf("uvar8 = %0x\n", uvar8.string()[i]);
    }
    printf("#############\n");
    result = DrmCtaUtil::getNormalFromUintVar(uvar8);
    if (result != normal)
    {
        printf("FAIL - test Two byte\n");
    } else
    {
        printf("SUCCESS - test Two bytes\n");
    }
    printf("result = 0x%x\n", result);

    //Test Three bytes
    printf("Test Three byte\n");
    normal = 0x87A5;
    uvar8 = DrmCtaUtil::getUintVarFromNormal(normal);
    printf("#############\n");
    for (size_t i = 0; i < uvar8.size(); ++i)
    {
        printf("uvar8 = %0x\n", uvar8.string()[i]);
    }
    printf("#############\n");
    result = DrmCtaUtil::getNormalFromUintVar(uvar8);
    if (result != normal)
    {
        printf("FAIL - test Three bytes\n");
    }else
    {
        printf("SUCCESS - test Three bytes\n");
    }
    printf("result = 0x%x\n", result);

    //Test Four bytes
    printf("Test Four byte\n");
    normal = 0x0FFFFFFE;
    uvar8 = DrmCtaUtil::getUintVarFromNormal(normal);
    printf("#############\n");
    for (size_t i = 0; i < uvar8.size(); ++i)
    {
        printf("uvar8 = %0x\n", uvar8.string()[i]);
    }
    printf("#############\n");
    result = DrmCtaUtil::getNormalFromUintVar(uvar8);
    if (result != normal)
    {
        printf("FAIL - test Four bytes\n");
    }else
    {
        printf("SUCCESS - test Four bytes\n");
    }
    printf("result = 0x%x\n", result);

    //Test Five bytes
    printf("Test Five byte\n");
    normal = 0x8FFFFFFF;
    uvar8 = DrmCtaUtil::getUintVarFromNormal(normal);
    printf("#############\n");
    for (size_t i = 0; i < uvar8.size(); ++i)
    {
        printf("uvar8 = %0x\n", uvar8.string()[i]);
    }
    printf("#############\n");
    result = DrmCtaUtil::getNormalFromUintVar(uvar8);
    if (result != normal)
    {
        printf("FAIL - test Five bytes\n");
    }else
    {
        printf("SUCCESS - test Five bytes\n");
    }
    printf("result = 0x%x\n", result);

}


DrmCtaUtil::DrmCtaUtil()
{

}

String8 DrmCtaUtil::getErrorCallbackMsg(String8 path, String8 flag)
{
    if (String8("") == path)
    {
        ALOGD("hongen:error path");
        path = "error";
    }
    String8 str("data_s:0::cnt_s:0::path:");
    str.append(path);
    str.append("::result:");
    str.append(flag);
    return str;
}

bool DrmCtaUtil::notify(const Vector<DrmCtaUtil::Listener> *infoListener, String8 progress)
{
    /*for (Vector<DrmCtaUtil::Listener>::const_iterator iter = infoListener->begin();
            iter != infoListener->end(); ++iter)
    {
        DrmInfoEvent event(iter->GetUniqueId(), 10001,
                progress);
        iter->GetListener()->onInfo(event);
    }*/
    //ALOGD("hongen encrypt: notify-progress=[%s]",progress.string());
    for (size_t i = 0; i < infoListener->size(); i++)
    {
        DrmInfoEvent event((*infoListener)[i].GetUniqueId(), DrmDef::CTA5_CALLBACK, progress);
//        ALOGD("hongen encrypt: notify---,");
        (*infoListener)[i].GetListener()->onInfo(event);
    }
    return true;
}

bool DrmCtaUtil::isTrustCtaClient(pid_t pid)
{
    //IPCThreadState* ipcState = IPCThreadState::self();
    //uid_t uid = ipcState->getCallingUid();
    //pid_t pid = ipcState->getCallingPid();
    String8 processName = DrmMtkUtil::getProcessName(pid);
    ALOGD("processName = %s",processName.string());
    ALOGD("pid = %d", pid);
    return DrmMtkDefender::isCtaTrustedClient(processName);
}

bool DrmCtaUtil::isTrustCtaClient(String8 &processName)
{
    return DrmMtkDefender::isCtaTrustedClient(processName);
}

bool DrmCtaUtil::IsCtaTrustedCheckTokenClient(String8 &processName)
{
    return DrmMtkDefender::isCtaTrustedClient(processName);
}

bool DrmCtaUtil::IsCtaTrustedGetTokenClient(String8 &processName)
{
    return DrmMtkDefender::isCtaTrustedClient(processName);
}
