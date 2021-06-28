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

#ifndef RO_H_
#define RO_H_

#include "DrmDef.h"
#include <utils/String8.h>

namespace android
{

class Entry
{
public:
    Entry();
    void dump();

public:
    int next;
    int type;
    long used_count;
    long total_count;
    long start_time;
    long end_time;
    long interval;
    long start_intv;
    long end_intv;
};

class Rights
{
public:
    Rights();
    ~Rights();
    void dump();
    String8 getGeneralStr();

public:
    char cid[DrmDef::DRM_MAX_META_LENGTH];
    char key[DrmDef::DRM_MAX_KEY_LENGTH];
    int permission;
    int num[DrmDef::PERMISSION_TOTAL_INDEX];
    int best[DrmDef::PERMISSION_TOTAL_INDEX];
    Entry* entryPtr;
};

// this is a dummy class only for old RO format compatibility purpose
class OldRights
{
public:
    // the old Rights format: the DrmDef::DRM_MAX_META_LENGTH == 100
    char cid[100];
    char key[DrmDef::DRM_MAX_KEY_LENGTH];
    int permission;
    int num[DrmDef::PERMISSION_TOTAL_INDEX];
    int best[DrmDef::PERMISSION_TOTAL_INDEX];
    Entry* entryPtr;
};

class RO
{
public:
    void dump();

public:
    Rights rights; // store in RO file
};

} // namespace android

#endif /* RO_H_ */
