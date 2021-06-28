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

//#define LOG_DEBUG 0
#define LOG_TAG "Utils_MTK"

#include <utils/Log.h>
#include <utils/String8.h>
#include <media/stagefright/MediaCodecList.h>

#include "Utils_MTK.h"

namespace android {


AString getProcessNameByPid(int pid) {
      // get the proc name by pid, via reading /proc/<pid>/cmdline file
      char path[30];
      snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
      AString result;
      FILE* fp = fopen(path, "r");
      if (NULL != fp) {
          char proc_name[100];
          bzero(proc_name, sizeof(proc_name));
          if (NULL != fgets(proc_name, sizeof(proc_name), fp)) {
              result.append(proc_name);
              ALOGD("getProcessNameByPid [%s]->[%s]", path, proc_name);
          } else {
              ALOGW("getProcessNameByPid failed to get processName [path:%s], reason [%s]",
                      path, strerror(errno));
          }
          fclose(fp);
      } else {
          ALOGW("getProcessNameByPid : failed to open [%s] , reason [%s]",
                  path, strerror(errno));
      }
      return result;
}

bool isMtkMp3Music(uint32_t app_pid) {
    bool isMtkSupportApp = false;
    AString proName = getProcessNameByPid((int)app_pid);
    const char *processName = proName.c_str();
    if(processName != NULL &&
        ((!strncasecmp(processName, "com.android.music", 17)) ||
        (!strncasecmp(processName, "com.google.android.music", 24)))) {
        ALOGV("it is mtk music.");
        isMtkSupportApp = true;
    }
    return isMtkSupportApp;
}

bool isFindMtkMp3Codec(const AString &mime, bool encoder) {
    Vector<AString> matchingCodecs;
    MediaCodecList::findMatchingCodecs(
                mime.c_str(),
                encoder,
                0,
                &matchingCodecs);

    if (matchingCodecs.size() == 0) {
        return false;
    }
    AString componentName = matchingCodecs[0];
    if (!strcmp(componentName.c_str(), "OMX.MTK.AUDIO.DECODER.MP3")) {
        ALOGV("Find mtk mp3 codec.");
        return true;
    }
    return false;
}


}
