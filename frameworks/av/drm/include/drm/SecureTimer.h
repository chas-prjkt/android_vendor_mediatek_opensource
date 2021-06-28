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

#ifndef SECURETIMER_H_
#define SECURETIMER_H_

#include <drm/drm_framework_common.h>
#include <utils/String8.h>
#include <utils/threads.h>
#include <time.h>

namespace android
{

class SecureTimer
{
public:
    static const int RESULT_OK = DRM_NO_ERROR;
    static const int RESULT_ERR = DRM_ERROR_UNKNOWN;

    static const int CLOCK_VALID = 0;
    static const int CLOCK_INVALID = -1;
    static const int CLOCK_NEED_SYNC = -2;

public:  // singleton pattern
    static SecureTimer& instance(void);

private:  // avoid explicit construct
    SecureTimer();
    SecureTimer(const SecureTimer& copy);
    SecureTimer& operator=(SecureTimer& other);

public:
    ~SecureTimer();

public:
    bool isValid();
    int updateTimeBase();
    int updateOffset();
    int updateDRMTime(time_t offset);
    int getDRMTime(time_t& t); // time_t: long in linux
    time_t getOffset();
    int load();
    int save();
    void reset();

private:
    time_t deviceTime();
    time_t deviceTicks();

private:
    static SecureTimer* m_pTimer; // for singleton pattern
    bool m_bIsValid;    // ture if the secure clock is in valid state
    time_t m_nOffset;   // in seconds, (t_device + offset == t_real)
    time_t m_nBaseTicks;// in seconds, the interval since last boot of system
    time_t m_nBaseTime; // in seconds, the device time value
    time_t m_nLastSync; // in seconds, the time after the offset is synchronized by SNTP
    time_t m_nLastSave; // in seconds, the time every time the secure clock state is saved

private:
    static Mutex mLock;
};

} // namespace android

#endif /* SECURETIMER_H_ */
