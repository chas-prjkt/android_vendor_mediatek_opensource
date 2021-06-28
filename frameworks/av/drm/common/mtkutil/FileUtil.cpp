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

#define LOG_NDEBUG 0
#define LOG_TAG "DrmMtkUtil/FileUtil"
#include <utils/Log.h>

#include <FileUtil.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

using namespace android;

bool FileUtil::fopenx(const char* filename, const char* mode, FILE** fp)
{
    *fp = fopen(filename, mode);
    if (*fp == NULL)
    {
        ALOGE("fopenx: failed to open file [%s] using mode [%s], reason [%s]",
                filename, mode, strerror(errno));
        return false;
    }
    return true;
}

bool FileUtil::fclosex(FILE* fp)
{
    if (NULL == fp)
    {
        ALOGD("fclosex: NULL file pointer.");
        return true;
    }

    if (fclose(fp) != 0)
    {
        ALOGE("fclosex: failed to close file.");
        return false;
    }
    return true;
}

bool FileUtil::fseekx(FILE* fp, long int offset, int origin)
{
    if (fseek(fp, offset, origin) != 0)
    {
        ALOGE("fseekx: faild to seek to offset [%ld] from origin type [%d], reason [%s]",
                offset, origin, strerror(errno));
        return false;
    }
    return true;
}

bool FileUtil::fwritex(void* ptr, size_t size, FILE* fp)
{
    size_t writeSize = fwrite(ptr, size, 1, fp);
    if (writeSize != 1)
    {
        ALOGE("fwritex: failed to write [%d] amount of data to file, reason [%s]",
                size, strerror(errno));
        return false;
    }
    return true;
}

bool FileUtil::freadx(void* ptr, size_t size, FILE* fp)
{
    size_t readSize = fread(ptr, size, 1, fp);
    if (readSize != 1)
    {
        ALOGE("freadx: failed to read [%d] amount of data from file, reason [%s]",
                size, strerror(errno));
        return false;
    }
    return true;
}

bool FileUtil::ftellx(FILE* fp, long int& pos)
{
    pos = ftell(fp);
    if (pos == -1L)
    {
        ALOGE("ftellx: failed to get current fp position, reason [%s]", strerror(errno));
        return false;
    }
    return true;
}

// get one line from input file
// result contains CR LF, and NULL terminator
bool FileUtil::fgetsx(FILE* fp, char* str, int num)
{
    char* p = fgets(str, num, fp);
    if (p == NULL)
    {
        if (feof(fp) != 0) // reach end of file
        {
            ALOGE("fgetsx: reach EOF and nothing read.");
            return false;
        }
        else if (ferror(fp) != 0)
        {
            ALOGE("fgetsx: faild to get a line from file.");
            return false;
        }
    }
    return true;
}
