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

#include <ByteBuffer.h>
#include <string.h>

using namespace android;

ByteBuffer::ByteBuffer() : mBuffer(NULL), mLen(0)
{
}

ByteBuffer::ByteBuffer(char* b, size_t len)
{
    allocate((const char*)b, len);
}

ByteBuffer::ByteBuffer(const char* b, size_t len)
{
    allocate(b, len);
}

ByteBuffer::ByteBuffer(char* str)
{
    allocate((const char*)str, strlen(str));
}

ByteBuffer::ByteBuffer(const char* str)
{
    allocate(str, strlen(str));
}

ByteBuffer::ByteBuffer(const ByteBuffer& copy)
{
    allocate(copy.mBuffer, copy.mLen);
}

ByteBuffer& ByteBuffer::operator=(const ByteBuffer& other)
{
    cleanUp();
    allocate(other.mBuffer, other.mLen);
    return *this;
}

ByteBuffer::~ByteBuffer()
{
    cleanUp();
}

const char* ByteBuffer::buffer() const
{
    return mBuffer;
}

size_t ByteBuffer::length() const
{
    return mLen;
}

void ByteBuffer::setTo(char* b, size_t len)
{
    setTo((const char*)b, len);
}

void ByteBuffer::setTo(const char* b, size_t len)
{
    cleanUp();
    allocate(b, len);
}

void ByteBuffer::setTo(char* str)
{
    setTo((const char*)str);
}

void ByteBuffer::setTo(const char* str)
{
    setTo(str, strlen(str));
}

void ByteBuffer::allocate(const char* b, size_t len)
{
    if (NULL == b || 0 == len)
    {
        mBuffer = NULL;
        mLen = 0;
    }
    else
    {
        mBuffer = new char[len];
        memset(mBuffer, 0, len);
        memcpy(mBuffer, b, len);
        mLen = len;
    }
}

void ByteBuffer::cleanUp()
{
    if (NULL != mBuffer)
    {
        delete[] mBuffer;
        mBuffer = NULL;
    }
    mLen = 0;
}
