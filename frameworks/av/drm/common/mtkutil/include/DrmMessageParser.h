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

#ifndef DRM_MESSAGE_PARSER_H_
#define DRM_MESSAGE_PARSER_H_

#include <utils/String8.h>

namespace android {

// the syntax of Content-Type header is defined in RFC 2045 chapter 5.1
class ContentType {
public:
    explicit ContentType(const char* inputLine);
private:
    ContentType(const ContentType& copy);
    ContentType& operator=(const ContentType& other);

public:
    bool IsValid();
    String8 type;
    String8 subType;
    String8 mediaType;
};

// the syntax of Content-Transfer-Encoding header is defined in RFC 2045 chapter 6.1
class ContentTransferEncoding {
public:
    explicit ContentTransferEncoding(const char* inputLine);
private:
    ContentTransferEncoding(const ContentTransferEncoding& copy);
    ContentTransferEncoding& operator=(const ContentTransferEncoding& other);

public:
    bool IsValid();
    String8 mechanism;
};

class ContentId {
public:
    explicit ContentId(const char* inputLine);
private:
    ContentId(const ContentId& copy);
    ContentId& operator=(const ContentId& other);

public:
    bool IsValid();
    String8 id;
};

class ContentDescription {
public:
    explicit ContentDescription(const char* inputLine);
private:
    ContentDescription(const ContentDescription& copy);
    ContentDescription& operator=(const ContentDescription& other);

public:
    bool IsValid();
    String8 description;
};

} // namespace android

#endif // DRM_MESSAGE_PARSER_H_
