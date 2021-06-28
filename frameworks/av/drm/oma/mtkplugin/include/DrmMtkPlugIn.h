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

#ifndef __DRM_MTK_PLUGIN_H__
#define __DRM_MTK_PLUGIN_H__

#include <DrmEngineBase.h>
#include <SessionMap.h>

#include <DrmDef.h>
#include <DrmTypeDef.h>

#include <string.h>
#include <strings.h>
#include <unistd.h>

namespace android
{

class DrmMtkPlugIn: public DrmEngineBase
{

public:
    DrmMtkPlugIn();
    virtual ~DrmMtkPlugIn();

protected:
    DrmConstraints* onGetConstraints(int uniqueId, const String8* path,
            int action);

    DrmMetadata* onGetMetadata(int uniqueId, const String8* path);

    status_t onInitialize(int uniqueId);

    status_t onSetOnInfoListener(int uniqueId,
            const IDrmEngine::OnInfoListener* infoListener);

    status_t onTerminate(int uniqueId);

    bool onCanHandle(int uniqueId, const String8& path);

    DrmInfoStatus* onProcessDrmInfo(int uniqueId, const DrmInfo* drmInfo);

    status_t onSaveRights(int uniqueId, const DrmRights& drmRights,
            const String8& rightsPath, const String8& contentPath);

    DrmInfo* onAcquireDrmInfo(int uniqueId,
            const DrmInfoRequest* drmInfoRequest);

    String8 onGetOriginalMimeType(int uniqueId, const String8& path, int fd);

    int onGetDrmObjectType(int uniqueId, const String8& path,
            const String8& mimeType);

    int onCheckRightsStatus(int uniqueId, const String8& path, int action);

    status_t onConsumeRights(int uniqueId, sp<DecryptHandle>& decryptHandle,
            int action, bool reserve);

    status_t onSetPlaybackStatus(int uniqueId, sp<DecryptHandle>& decryptHandle,
            int playbackStatus, int64_t position);

    bool onValidateAction(int uniqueId, const String8& path, int action,
            const ActionDescription& description);

    status_t onRemoveRights(int uniqueId, const String8& path);

    status_t onRemoveAllRights(int uniqueId);

    status_t onOpenConvertSession(int uniqueId, int convertId);

    DrmConvertedStatus* onConvertData(int uniqueId, int convertId,
            const DrmBuffer* inputData);

    DrmConvertedStatus* onCloseConvertSession(int uniqueId, int convertId);

    DrmSupportInfo* onGetSupportInfo(int uniqueId);

    status_t onOpenDecryptSession(int uniqueId, sp<DecryptHandle>& decryptHandle,
            int fd, off64_t offset, off64_t length);

    status_t onOpenDecryptSession(int uniqueId, sp<DecryptHandle>& decryptHandle,
            const char* uri);

    status_t onCloseDecryptSession(int uniqueId, sp<DecryptHandle>& decryptHandle);

    status_t onInitializeDecryptUnit(int uniqueId,
            sp<DecryptHandle>& decryptHandle, int decryptUnitId,
            const DrmBuffer* headerInfo);

    status_t onDecrypt(int uniqueId, sp<DecryptHandle>& decryptHandle,
            int decryptUnitId, const DrmBuffer* encBuffer,
            DrmBuffer** decBuffer, DrmBuffer* IV);

    status_t onFinalizeDecryptUnit(int uniqueId, sp<DecryptHandle>& decryptHandle,
            int decryptUnitId);

    ssize_t onPread(int uniqueId, sp<DecryptHandle>& decryptHandle, void* buffer,
            ssize_t numBytes, off64_t offset);

    /*
     * an inner class for storing necessary information needed for decryption.
     */
private:
    class DecryptSession
    {
    private:
        DecryptSession() :
            m_fileDesc(-1), m_dataOffset(0), m_dataLength(0)
        {
            bzero(m_key, DrmDef::DRM_MAX_KEY_LENGTH);
        }

    public:
        DecryptSession(int fd, int offset, int length, BYTE* key) :
            m_fileDesc(fd), m_data(NULL), m_dataOffset(offset), m_dataLength(length)
        {
            memcpy(m_key, key, DrmDef::DRM_MAX_KEY_LENGTH);
        }

        DecryptSession(void* data, int offset, int length, BYTE* key) :
            m_fileDesc(0), m_data(data), m_dataOffset(offset), m_dataLength(length)
        {
            memcpy(m_key, key, DrmDef::DRM_MAX_KEY_LENGTH);
        }

        ~DecryptSession()
        {
            // close fd
            if (m_fileDesc > -1)
            {
                close(m_fileDesc);
            }
        }

    public:
        int m_fileDesc;
        void* m_data;
        int m_dataOffset;
        int m_dataLength;
        BYTE m_key[DrmDef::DRM_MAX_KEY_LENGTH];
    };

    /*
     * an inner class for storing necessary information needed for converting
     *   .dm content file into .dcf format.
     */
private:
    class ConvertSession
    {
    public:
        ConvertSession() : m_uniqueId(0)
        {
        }

        ~ConvertSession()
        {
        }

    public:
        int m_uniqueId;
    };

    /**
     * Session Map Tables for Conversion and Decoding of forward lock files.
     */
private:
    SessionMap<ConvertSession*> m_convertSessionMap;
    SessionMap<DecryptSession*> m_decryptSessionMap;

private:
    sp<DecryptHandle> openDecryptSessionImpl();
    status_t openDecryptSessionWithBuffer(int uniqueId, sp<DecryptHandle>& decryptHandle,
            const DrmBuffer& buf, const off64_t offset, const String8& mimeType);

private:
    bool m_bFwdLockOnly;
};



} // namespace android

#endif /* __DRM_MTK_PLUGIN_H__ */
