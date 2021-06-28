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

#ifndef SECURETIMERHELPER_H_
#define SECURETIMERHELPER_H_

#include <time.h>

namespace android
{

class SecureTimerHelper
{
public:
    static const int NTP_SYNC_SUCCESS;
    static const int NTP_SYNC_NETWORK_TIMEOUT;
    static const int NTP_SYNC_SERVER_TIMEOUT;
    static const int NTP_SYNC_NETWORK_ERROR;
    static const int NTP_SYNC_INVALID_OFFSET;

public:
    // implements SNTP time synchronization
    // get the time offset, between the current device time and real time
    // realTime = deviceTime[current] + Offset
    // returns the error information or NTP_SYNC_SUCCESS;
    // {offset} is set to 0 if fails, otherwise the actuall offset
    static int syncNTPTime(time_t& offset);

public:
    static int syncNTPTime(time_t& offset, const char* svr_addr, int addr_type);
};

} // namespace android

#endif /* SECURETIMERHELPER_H_ */
