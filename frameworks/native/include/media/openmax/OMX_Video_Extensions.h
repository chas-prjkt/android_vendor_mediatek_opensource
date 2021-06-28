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

#ifndef __OMX_VIDEO_EXTENSIONS_H__
#define __OMX_VIDEO_EXTENSIONS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <OMX_Core.h>

#pragma pack(push, 1)

typedef enum OMX_VIDEO_SliceControlMode
{
    OMX_VIDEO_SliceControlModeNone        = 0,
    OMX_VIDEO_SliceControlModeMB          = 1,
    OMX_VIDEO_SliceControlModeByte        = 2,
    OMX_VIDEO_SliceControlModMBRow        = 3,
} OMX_VIDEO_SliceControlMode;

typedef enum OMX_VIDEO_DownScaleFactor
{
    OMX_VIDEO_DownScaleFactor_1_1         = 0,
    OMX_VIDEO_DownScaleFactor_Equal_AR    = 1,
    OMX_VIDEO_DownScaleFactor_Any         = 2,
} OMX_VIDEO_DownScaleFactor;

typedef enum OMX_VIDEO_HierarType
{
    OMX_VIDEO_HierarType_P                = 0x01,
    OMX_VIDEO_HierarType_B                = 0x02,
} OMX_VIDEO_HierarType;

typedef enum OMX_VIDEO_EXTENSION_AVCPROFILETYPE
{
    OMX_VIDEO_EXT_AVCProfileConstrainedBaseline = 0x01,
    OMX_VIDEO_EXT_AVCProfileConstrainedHigh     = 0x02,
} OMX_VIDEO_EXTENSION_AVCPROFILETYPE;

typedef struct OMX_VIDEO_ENCODERPARAMS {
    OMX_BOOL bLowLatency;
    OMX_BOOL bUseExtendedProfile;
    OMX_BOOL bSequenceHeaderWithIDR;
    OMX_VIDEO_EXTENSION_AVCPROFILETYPE eProfile;
    OMX_U32 nLTRFrames;
    OMX_VIDEO_HierarType eHierarType;
    OMX_U32 nMaxTemporalLayerCount;
    OMX_VIDEO_SliceControlMode eSliceControlMode;
    OMX_U32 nSarIndex;
    OMX_U32 nSarWidth;
    OMX_U32 nSarHeight;
} OMX_VIDEO_ENCODERPARAMS;

typedef struct OMX_VIDEO_ENCODERCAP {
    OMX_BOOL bLowLatency;
    OMX_U32 nMaxFrameWidth;
    OMX_U32 nMaxFrameHeight;
    OMX_U32 nMaxInstances;
    OMX_U32 nMaxTemporaLayerCount;
    OMX_U32 nMaxRefFrames;
    OMX_U32 nMaxLTRFrames;
    OMX_VIDEO_AVCLEVELTYPE nMaxLevel;
    OMX_U32 nSliceControlModesBM;
    OMX_U32 nMaxMacroblockProcessingRate;
    OMX_VIDEO_DownScaleFactor nResize;
    OMX_U32 xMinScaleFactor;
} OMX_VIDEO_ENCODERCAP;

typedef struct OMX_VIDEO_PARAM_ENCODERSETTING {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_VIDEO_ENCODERPARAMS stEncParam;
} OMX_VIDEO_PARAM_ENCODESETTING;

typedef struct OMX_VIDEO_PARAM_ENCODERCAP {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_VIDEO_ENCODERCAP stEncCap;
} OMX_VIDEO_PARAM_ENCODERCAP;

typedef struct OMX_VIDEO_CONFIG_MARKLTRFRAME {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nLongTermFrmIdx;
} OMX_VIDEO_CONFIG_MARKLTRFRAME;

typedef struct OMX_VIDEO_CONFIG_USELTRFRAME {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U16 nUsedLTRFrameBM;
} OMX_VIDEO_CONFIG_USELTRFRAME;

typedef struct OMX_VIDEO_CONFIG_QP {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nQP;
} OMX_VIDEO_CONFIG_QP;

typedef struct OMX_VIDEO_CONFIG_TEMPORALLAYERCOUNT {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nTemproalLayerCount;
} OMX_VIDEO_CONFIG_TEMPORALLAYERCOUNT;

typedef struct OMX_VIDEO_CONFIG_BASELAYERPID{
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nPID;
} OMX_VIDEO_CONFIG_BASELAYERPID;

typedef struct OMX_VIDEO_DECODERPARAMS {
    OMX_BOOL bLowLatency;
} OMX_VIDEO_DECODERPARAMS;

typedef struct OMX_VIDEO_DECODERCAP {
    OMX_BOOL bLowLatency;
    OMX_U32 nMaxFrameWidth;
    OMX_U32 nMaxFrameHeight;
    OMX_U32 nMaxInstances;
    OMX_VIDEO_AVCLEVELTYPE nMaxLevel;
    OMX_U32 nMaxMacroblockProcessingRate;
} OMX_VIDEO_DECODERCAP;

typedef struct OMX_VIDEO_PARAM_DECODERCAP {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_VIDEO_DECODERCAP stDecoderCap;
} OMX_VIDEO_PARAM_DECODERCAP;

typedef struct OMX_VIDEO_PARAM_DRIVERVER {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U64 nDriverVersion;
} OMX_VIDEO_PARAM_DRIVERVER;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif
