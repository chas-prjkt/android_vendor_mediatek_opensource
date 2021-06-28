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

#ifndef __DRM_MTK_DEF_H__
#define __DRM_MTK_DEF_H__

#include <utils/String8.h>
#include <utils/Vector.h>
#include <utils/threads.h>
#define NTP_SERVER_CNT 5

namespace android {

const unsigned int OMADrmFlag = 0x80; // 128

/*
* this defines those process that can access directly the decrypt content
* of OMA DRM v1 protected (by encryption) files.
*/
class DrmTrustedClient {
private:
    DrmTrustedClient();
    static Vector<String8> TRUSTED_PROC;
    static bool sIsInited;
    static bool init();

public:
    static bool IsDrmTrustedClient(const String8& procName);
};

/*
* this defines those process that can launch playback for those protected content
* of OMA DRM v1 while using default mediaplayer.
* the process which need to play OMA DRM v1 content (video/audio), and is using
* MediaPlayer instance, should be added to this white list. e.g. com.android.music
*/
class DrmTrustedApp {
private:
    DrmTrustedApp();
    static Vector<String8> TRUSTED_APP;
    static bool sIsInited;
    static bool init();

public:
    static bool IsDrmTrustedApp(const String8& procName);
};

/*
* this is defined for Mediatek default video playback applications (videoplayer)
* Note: normally you should not modify these
*/
class DrmTrustedVideoApp {
private:
    DrmTrustedVideoApp();
    static Vector<String8> TRUSTED_VIDEO_APP;
    static bool sIsInited;
    static bool init();

public:
    static bool IsDrmTrustedVideoApp(const String8& procName);
};

class DrmMtkDefender {
private:
    DrmMtkDefender();
    static Mutex sLock;
    static Vector<String8> DRM_TRUSTED_PROC;
    static Vector<String8> DRM_CONSUME_IN_APP_PROC;
    static Vector<String8> NEED_CONSUME_CID_LIST;
    static Vector<String8> CTA_TRUSTED_PROC;
    static bool sIsInited;
    static bool init();

public:
    static bool isDrmTrustedClient(const String8& procName);
    static bool isDrmConsumeInAppClient(const String8& procName);
    static bool markAsConsumeInAppClient(const String8& procName, const String8& cid);
    static bool isNeedConsume(const String8& cid);
    static bool isCtaTrustedClient(const String8& procName);

private:
    static bool sDebug;
};

/*
* this is defined for those servers which SNTP time synchronization will use
* Note: these are deprecated. The actuall definition is in DrmProvider
*/
class DrmSntpServer {
private:
    DrmSntpServer();

public:
    static const char* NTP_SERVER_1;
    static const char* NTP_SERVER_2;
    static const char* NTP_SERVER_3;
    static const char* NTP_SERVER_4;
    static const char* NTP_SERVER_5;
};

/*
* defined for OMA DRM v1 file's meta-data keys
*/
class DrmMetaKey {
private:
    DrmMetaKey();

public:
    static const char* META_KEY_IS_DRM;
    static const char* META_KEY_CONTENT_URI;
    static const char* META_KEY_OFFSET;
    static const char* META_KEY_DATALEN;
    static const char* META_KEY_RIGHTS_ISSUER;
    static const char* META_KEY_CONTENT_NAME;
    static const char* META_KEY_CONTENT_DESCRIPTION;
    static const char* META_KEY_CONTENT_VENDOR;
    static const char* META_KEY_ICON_URI;
    static const char* META_KEY_METHOD;
    static const char* META_KEY_MIME;
};

class CtaTrustedClient {
private:
    CtaTrustedClient();
    static Vector<String8> TRUSTED_PROC;
    static Vector<String8> TRUSTED_GETTOKEN_PROC;
    static Vector<String8> TRUSTED_CHECKTOKEN_PROC;
    static bool sIsInited;
    static bool init();
    static bool initTrustedClient();
    static bool initTrustedGetTokenClient();
    static bool initTrustedCheckTokenClient();

public:
    static bool IsCtaTrustedClient(const String8& procName);
    static bool IsCtaTrustedGetTokenClient(const String8& procName);
    static bool IsCtaTrustedCheckTokenClient(const String8& procName);

};
}

#endif // __DRM_MTK_DEF_H__
