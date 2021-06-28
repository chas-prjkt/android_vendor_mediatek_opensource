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

#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#include <string.h>

namespace android
{

class ByteBuffer
{
public:
    ByteBuffer();
    explicit ByteBuffer(char* b, size_t len);
    explicit ByteBuffer(const char* b, size_t len);
    explicit ByteBuffer(char* str); // the input is treated like a string thus the data after a '\0'
                                    // character will be cut off.
    explicit ByteBuffer(const char* str);

    ByteBuffer(const ByteBuffer& copy);

    ByteBuffer& operator=(const ByteBuffer& other);

    ~ByteBuffer();

public:
    const char* buffer() const;
    size_t length() const;

    void setTo(char* b, size_t len);
    void setTo(const char* b, size_t len);
    void setTo(char* str); // the input is treated like a string
    void setTo(const char* str);

private:
    void allocate(const char* b, size_t len);
    void cleanUp();

private:
    char* mBuffer;
    int mLen;
};

} // namespace android

#endif // _BYTEBUFFER_H_
