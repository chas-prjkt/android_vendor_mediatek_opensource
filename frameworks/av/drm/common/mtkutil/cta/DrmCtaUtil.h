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

#ifndef __DRM_CTA_UTIL_H__
#define __DRM_CTA_UTIL_H__

#include <drm/drm_framework_common.h>
#include <DrmEngineBase.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <utils/threads.h>
#include <stdio.h>

namespace android {

class DrmCtaUtil {
public:
    DrmCtaUtil();

public:
    /*
     * Get the file full path from fd
     */
    static String8 getPathFromFd(int fd);
    /**
     * Generate a Uintvar format value from a normal value
     */
    static String8 getUintVarFromNormal(uint32_t normal);
    /**
     * Get normal value from a Uintvar format value
     */
    static uint32_t getNormalFromUintVar(String8 uvar);

    static String8 getErrorCallbackMsg(String8 path, String8 flag);
private:
    String8 mCtaKey;
    //static vector<String8> sCtaWhiteList;

public:
    class Listener {
        public:
            Listener() : mListener(NULL), mUniqueId(-1) {}

            Listener(IDrmEngine::OnInfoListener *listener, int uniqueId)
                : mListener(listener), mUniqueId(uniqueId) {};

            IDrmEngine::OnInfoListener *GetListener() const {return mListener;}
            int GetUniqueId() const {return mUniqueId;}

        private:
            IDrmEngine::OnInfoListener *mListener;
            int mUniqueId;
    };

public:
    static bool notify(const Vector<DrmCtaUtil::Listener> *infoListener, String8 progress);
    static bool isTrustCtaClient(pid_t pid);
    static bool isTrustCtaClient(String8 &processName);
    static bool IsCtaTrustedCheckTokenClient(String8 &processName);
    static bool IsCtaTrustedGetTokenClient(String8 &processName);
};

}

#endif // __DRM_CTA_UTIL_H__
