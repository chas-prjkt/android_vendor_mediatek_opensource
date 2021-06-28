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

#ifndef STRUTIL_H_
#define STRUTIL_H_


#include <utils/String8.h>
#include <time.h>

namespace android
{

class StrUtil
{
public:
    static const char* toString(long l); // need not to delete the returned string buffer
    static const char* toString(int i);

    static void toLower(char* p);
    static String8 toHexStr(String8 str);
    static String8 toHexStr(char* ptr, int num);
    static String8 toTimeStr(time_t* t);
    static bool intervalStrToTick(char* p, time_t& tick);
    static bool datetimeStrToTick(char* p, time_t& tick);
    static String8& trimLRSpace(String8& str);
    static char* strrpl(char* s, const char* s1, const char* s2);
    static String8& trimRCRLF(String8& str);
    static String8 getContentUri(String8 cid);
private:
    static bool validateDatetime(const struct tm& time);
    static bool validateDatetimeStr(const char* ptr,const int& len);
};

}

#endif /* STRUTIL_H_ */
