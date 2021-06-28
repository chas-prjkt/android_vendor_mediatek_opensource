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

#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include <stdio.h>

namespace android
{

class FileUtil
{
public:
    static bool fopenx(const char* filename, const char* mode, FILE** fp);
    static bool fclosex(FILE* fp);
    static bool fseekx(FILE* fp, long int offset, int origin);
    static bool fwritex(void* ptr, size_t size, FILE* fp);
    static bool freadx(void* ptr, size_t size, FILE* fp);
    static bool ftellx(FILE* fp, long int& pos);
    static bool fgetsx(FILE* fp, char* str, int num);
};

}

#endif /* FILEUTIL_H_ */
