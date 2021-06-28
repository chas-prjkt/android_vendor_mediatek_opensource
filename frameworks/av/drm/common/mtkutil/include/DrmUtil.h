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

#ifndef DRMUTIL_H_
#define DRMUTIL_H_

#include "RO.h"
#include "ByteBuffer.h"

#include <drm/drm_framework_common.h>
#include <drm/DrmMetadata.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <utils/String8.h>
#include <utils/threads.h>

#include <stdio.h>

namespace android
{

class Mode
{
public:
    static const int ConsumeRights = 0x00;
    static const int CheckRightsStatus = 0x01;
    static const int GetConstraints = 0x02;
};

class DrmUtil
{
public:
    static bool checkDir(String8 dir);
    static bool checkExistence(String8 filePath);

    static String8 getROFileName(String8 cid);

    static bool restore(String8 cid, RO* ro);
    static bool save(RO* ro);
    static bool merge(RO* newRO);

    static int checkRightsStatus(String8 method, String8 cid, int action);
    static bool checkRightsStatus(String8 cid, int action);

    static bool consumeRights(String8 method, String8 cid, int action);
    static bool consumeRights(String8 path, int action);

    static bool getConstraints(String8 cid, int action, Entry& outEntry);

    static bool parse_dr(DrmBuffer& drmBuffer, RO* ro);
    static bool parse_drc(DrmBuffer& drmBuffer, RO* ro);

    static bool parseDcf(String8 path, DrmMetadata* metadataPtr);
    static int parseDcf(int fd, DrmMetadata* metadataPtr);
    // Add for Decode image with open decrypt seesion with ashmem
    static int parseDcf(const DrmBuffer& drmBuffer, DrmMetadata* metadataPtr);

    static bool checkDcf(String8 path, char* mime);
    static int checkDcf(int fd, char* mime);

    static ByteBuffer getDcfDrmKey(DrmMetadata* pMetaData);
    static ByteBuffer getDrmKey();

    static ByteBuffer base64_decode_bytebuffer(ByteBuffer& buf);
    static void base64_decrypt_buffer(unsigned char* input, unsigned char* output, int inputLength, int& outputLength);
    static void rc4_encrypt_buffer(unsigned char* toBuffer, unsigned char* fromBuffer, int size);
    static void rc4_decrypt_buffer(unsigned char* toBuffer, unsigned char* fromBuffer, int size);
    static String8 hash(char* seed, int seedLen);
    /*
     * Get the file full path from fd
     */
    static String8 getPathFromFd(int fd);

public:
    // checkDir
    static void CreateMulvPath(char* muldir);

    // restore
    static bool restoreRights(FILE* fp, RO* ro);
    static bool restoreEntry(String8 ro_file, FILE* fp, RO* ro);

    // save
    static bool saveRights(FILE* fp, Rights* rights);
    static bool saveEntry(FILE* fp, RO* ro);

    // restore & save
    static int getRightsPosition();

    // merge
    static bool mergeEntry(RO* newRO, int new_entry_index, int permission);
    static int compareEntry(Entry* e1, Entry* e2);
    static void getFirstAvailableEntryIndex(RO* ro, int* avIndex, int* entryNum);
    static int getEntryDistance(RO* ro, Entry* e1, Entry* e2);

    // checkRightsStatus, consumeRights, getContraints
    static bool traverseRights(String8 cid, int permission, int mode);
    static bool traverseRights(String8 cid, int permission, int mode, Entry& outEntry);

    // parse_dr
    static xmlNodePtr getNode(xmlDocPtr doc, String8 path);
    static xmlDocPtr getXmlDocPtr(DrmBuffer& drmBuffer);
    static xmlDocPtr getXmlDocPtr(String8 filePath, int offset, int len);

    // parseDcf
    static int readUintVar(FILE* fp);

    // common
    static bool isEntryValid(Entry* entry);
    static bool isEntryUsable(Entry* entry);
    static int getEntryNum(String8 ro_file); // deprecated, use with caution

    // others
    static String8 readIMEI();
    static String8 readId();
    static int saveId(const String8& id);

    // for secure timer
    static int getTZOffset();

public:
    static Mutex mROLock;
    static Mutex mDCFLock;
    static bool sDDebug;
    static bool sVDebug;

private:

    /**
     * MAC address like 00:11:ee:ff:aa:10
     */
    static void getMAC(String8& mac);

};

}

#endif /* DRMUTIL_H_ */
