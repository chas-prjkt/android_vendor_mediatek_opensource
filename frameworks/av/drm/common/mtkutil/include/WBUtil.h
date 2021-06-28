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

#ifndef WBUTIL_H_
#define WBUTIL_H_

#include "RO.h"

namespace android
{

class WB
{
public:
    WB(char* _p, int _len)
    {
        p = _p;
        offset = 0;
        len = _len;
    }

public:
    char* p;
    int offset;
    int len;
};

class WBUtil
{
public:
    static bool parseWbXml(char* buffer, int length, RO* ro);

private:
    static bool parseConstraint(WB& wb, int permission, RO* ro);
    static bool gotoNextStartTag(WB& wb);
    static bool gotoNextEndTag(WB& wb);
    static bool peekNextStartTag(WB& wb, char& ch);
    static bool gotoNextTag(WB& wb, bool start);
};

}

#endif /* WBUTIL_H_ */
