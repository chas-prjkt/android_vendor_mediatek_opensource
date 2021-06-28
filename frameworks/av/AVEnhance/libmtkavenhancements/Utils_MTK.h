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

#ifndef UTILS_MTK_H_

#define UTILS_MTK_H_

namespace android {

struct AString;

AString getProcessNameByPid(int pid);
bool isMtkMp3Music(uint32_t app_pid);

bool isFindMtkMp3Codec(const AString &mime, bool encoder);



}  // namespace android

#endif  // UTILS_MTK_H_
