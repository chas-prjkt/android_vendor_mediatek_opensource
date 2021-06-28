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

#ifndef _FILE_MONITOR_H_
#define _FILE_MONITOR_H_

void tag_log(int type, const char* tag, const char *fmt, ...);

#ifdef LOGD
#undef LOGD
#endif
#ifdef LOGW
#undef LOGW
#endif
#ifdef LOGE
#undef LOGE
#endif
#define LOGD(...) tag_log(0, "[WLAN-ASSISTANT]", __VA_ARGS__);
#define LOGW(...) tag_log(0, " WARNING: [WLAN-ASSISTANT]", __VA_ARGS__);
#define LOGE(...) tag_log(1, " ERR: [WLAN-ASSISTANT]", __VA_ARGS__);

void *wlan_files_monitor(void*);
#endif
