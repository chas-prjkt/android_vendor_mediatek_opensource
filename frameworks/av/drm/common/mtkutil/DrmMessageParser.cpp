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
#define LOG_TAG "DrmMtkUtil/DrmMessageParser"
#include <utils/Log.h>

#include <DrmMessageParser.h>
#include <DrmDef.h>
#include <StrUtil.h>

#include <utils/String8.h>

#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_LOG 0

using namespace android;

String8 parse(const char* inputLine, const String8& token);

// note that the media type, type, and sub type are all CASE-SENSITIVE!
ContentType::ContentType(const char* inputLine) :
    type(""), subType(""), mediaType("") {

    if (NULL == inputLine || 0 >= strlen(inputLine)) {
        ALOGE("ContentType: invalid input for Content-Type header");
        return;
    }

    String8 input(inputLine);
    // find token "Content-Type:" (note: we ignore upper case & lower case of token.)
    input.toLower();
    String8 token = DrmDef::HEADER_TOKEN_CONTENT_TYPE;
    token.toLower();
    ALOGV("ContentType: input string [%s], token [%s]", input.string(), token.string());

    ssize_t index = input.find(token);
    ssize_t pos = index + token.length();
    if (index < 0) {
        ALOGD("invalid Content-Type header format with string [%s]", inputLine);
        return;
    }
    ALOGV("ContentType: token index [%d]", index);

    index = input.find(":"); // we assume that ':' can always be found.
    pos = index + 1;

    input.setTo(inputLine); // resume upper case & lower case.

    input.setTo(&input.string()[pos], input.length() - (size_t)pos);
    ALOGV("ContentType: token value position [%d], token value [%s]", pos, input.string());

    // find ';' which is the beginning of "parameter"
    // and we currently just ignore parameters.
    String8 result(input);
    ssize_t index_para = input.find(";");
    if (index_para > 0) { // have some parameters
        result.setTo(result.string(), (size_t)index_para);
    }
    result = StrUtil::trimLRSpace(result);
    ALOGD("ContentType: parsed media type: [%s]", result.string());

    // find '/' which is the separater of type and subtype
    ssize_t index_sprt = result.find("/");
    if (index_sprt < 0) {
        ALOGE("ContentType: invalid media type format with string [%s]", result.string());
        return;
    }
    mediaType = result;

    // the "type" and "sub type", e.g. type=="image" subType=="jpeg"
    type.setTo(result.string(), (size_t)index_sprt);
    subType.setTo(&result.string()[index_sprt + 1], result.length() - (size_t)index_sprt);
    ALOGD("ContentType: parsed type: [%s], sub type: [%s]", type.string(), subType.string());
}

bool ContentType::IsValid() {
    return !mediaType.isEmpty() && !type.isEmpty() && !subType.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////
// the Content-Transfer-Encoding is NOT CASE-SENSITIVE
// so we change it to lower-case finally
ContentTransferEncoding::ContentTransferEncoding(const char* inputLine) :
    mechanism("") {
    mechanism = parse(inputLine, DrmDef::HEADER_TOKEN_ENCODING);
    mechanism.toLower();
}

bool ContentTransferEncoding::IsValid() {
    return !mechanism.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////
ContentId::ContentId(const char* inputLine) :
    id("") {
    id = parse(inputLine, DrmDef::HEADER_TOKEN_ID);
}

bool ContentId::IsValid() {
    return !id.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////
ContentDescription::ContentDescription(const char* inputLine) :
    description("") {
    description = parse(inputLine, DrmDef::HEADER_TOKEN_DESCRIPTION);
}

bool ContentDescription::IsValid() {
    return !description.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////
String8 parse(const char* inputLine, const String8& token) {

    if (NULL == inputLine || 0 >= strlen(inputLine)) {
        ALOGE("parse: invalid input for MIME header [%s]", token.string());
        return String8("");
    }

    String8 input(inputLine);
    if (DEBUG_LOG) ALOGD("parse: >>> input string [%s]", input.string());
    input.toLower();
    String8 tk = token;
    tk.toLower();
    if (DEBUG_LOG) ALOGD("parse: >>> token [%s]", tk.string());

    // find token
    ssize_t index = input.find(tk);
    if (index < 0) {
        ALOGE("parse: failed to find token, invalid MIME header format with string [%s]",
                inputLine);
        return String8("");
    }
    if (DEBUG_LOG) ALOGD("parse: >>> token index [%d]", index);

    index = input.find(":"); // we assume that ':' can always be found.
    ssize_t pos = index + 1;

    input.setTo(inputLine); // resume upper case & lower case.

    input.setTo(&input.string()[pos], input.length() - (size_t)pos);
    if (DEBUG_LOG) ALOGD("parse: >>> token value position [%d], token value [%s]", pos, input.string());

    String8 result(input);
    result = StrUtil::trimLRSpace(result);
    ALOGD("parse: >>> parsed value: [%s]", result.string());

    return result;
}
