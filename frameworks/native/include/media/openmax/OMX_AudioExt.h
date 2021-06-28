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

/** OMX_AudioExt.h - OpenMax IL version 1.1.2
 * The OMX_AudioExt header file contains extensions to the
 * definitions used by both the application and the component to
 * access video items.
 */

#ifndef OMX_AudioExt_h
#define OMX_AudioExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Core.h>

#define OMX_AUDIO_AACToolAndroidSSBR (OMX_AUDIO_AACToolVendor << 0) /**< SSBR: MPEG-4 Single-rate (downsampled) Spectral Band Replication tool allowed or active */
#define OMX_AUDIO_AACToolAndroidDSBR (OMX_AUDIO_AACToolVendor << 1) /**< DSBR: MPEG-4 Dual-rate Spectral Band Replication tool allowed or active */

typedef enum OMX_AUDIO_CODINGEXTTYPE {
    OMX_AUDIO_CodingAndroidUnused = OMX_AUDIO_CodingKhronosExtensions + 0x00100000,
    OMX_AUDIO_CodingAndroidAC3,         /**< AC3 encoded data */
    OMX_AUDIO_CodingAndroidOPUS,        /**< OPUS encoded data */
    OMX_AUDIO_CodingAndroidEAC3,        /**< EAC3 encoded data */
    OMX_AUDIO_CodingAndroidAC4,         /**< AC4 encoded data */
} OMX_AUDIO_CODINGEXTTYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_AC3TYPE {
    OMX_U32 nSize;                 /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;      /**< OMX specification version information */
    OMX_U32 nPortIndex;            /**< port that this structure applies to */
    OMX_U32 nChannels;             /**< Number of channels */
    OMX_U32 nSampleRate;           /**< Sampling rate of the source data.  Use 0 for
                                        variable or unknown sampling rate. */
} OMX_AUDIO_PARAM_ANDROID_AC3TYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_EAC3TYPE {
    OMX_U32 nSize;                 /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;      /**< OMX specification version information */
    OMX_U32 nPortIndex;            /**< port that this structure applies to */
    OMX_U32 nChannels;             /**< Number of channels */
    OMX_U32 nSampleRate;           /**< Sampling rate of the source data.  Use 0 for
                                        variable or unknown sampling rate. */
} OMX_AUDIO_PARAM_ANDROID_EAC3TYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_AC4TYPE {
    OMX_U32 nSize;                 /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;      /**< OMX specification version information */
    OMX_U32 nPortIndex;            /**< port that this structure applies to */
    OMX_U32 nChannels;             /**< Number of channels */
    OMX_U32 nSampleRate;           /**< Sampling rate of the source data.  Use 0 for
                                                            variable or unknown sampling rate. */
} OMX_AUDIO_PARAM_ANDROID_AC4TYPE;


typedef struct OMX_AUDIO_PARAM_ANDROID_OPUSTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U32 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the encoded data data.  Use 0 for variable
                                   rate or unknown bit rates. Encoding is set to the
                                   bitrate closest to specified  value (in bps) */
    OMX_U32 nSampleRate;      /**< Sampling rate of the source data.  Use 0 for
                                   variable or unknown sampling rate. */
    OMX_U32 nAudioBandWidth;  /**< Audio band width (in Hz) to which an encoder should
                                   limit the audio signal. Use 0 to let encoder decide */
} OMX_AUDIO_PARAM_ANDROID_OPUSTYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_AACPRESENTATIONTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_S32 nMaxOutputChannels;    /**< Maximum channel count to be output, -1 if unspecified, 0 if downmixing disabled */
    OMX_S32 nDrcCut;               /**< The DRC attenuation factor, between 0 and 127, -1 if unspecified */
    OMX_S32 nDrcBoost;             /**< The DRC amplification factor, between 0 and 127, -1 if unspecified */
    OMX_S32 nHeavyCompression;     /**< 0 for light compression, 1 for heavy compression, -1 if unspecified */
    OMX_S32 nTargetReferenceLevel; /**< Target reference level, between 0 and 127, -1 if unspecified */
    OMX_S32 nEncodedTargetLevel;   /**< Target reference level assumed at the encoder, between 0 and 127, -1 if unspecified */
    OMX_S32 nPCMLimiterEnable;     /**< Signal level limiting, 0 for disable, 1 for enable, -1 if unspecified */
} OMX_AUDIO_PARAM_ANDROID_AACPRESENTATIONTYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_AACDRCPRESENTATIONTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_S32 nMaxOutputChannels;    /**< Maximum channel count to be output, -1 if unspecified, 0 if downmixing disabled */
    OMX_S32 nDrcCut;               /**< The DRC attenuation factor, between 0 and 127, -1 if unspecified */
    OMX_S32 nDrcBoost;             /**< The DRC amplification factor, between 0 and 127, -1 if unspecified */
    OMX_S32 nHeavyCompression;     /**< 0 for light compression, 1 for heavy compression, -1 if unspecified */
    OMX_S32 nTargetReferenceLevel; /**< Target reference level, between 0 and 127, -1 if unspecified */
    OMX_S32 nEncodedTargetLevel;   /**< Target reference level assumed at the encoder, between 0 and 127, -1 if unspecified */
    OMX_S32 nPCMLimiterEnable;     /**< Signal level limiting, 0 for disable, 1 for enable, -1 if unspecified */
    OMX_S32 nDrcEffectType;        /**< MPEG-D DRC effect type, between -1 and 6, -2 if unspecified */
} OMX_AUDIO_PARAM_ANDROID_AACDRCPRESENTATIONTYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_PROFILETYPE {
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;
   OMX_U32 nPortIndex;
   OMX_U32 eProfile;      /**< type is OMX_AUDIO_AACPROFILETYPE or OMX_AUDIO_WMAPROFILETYPE
                                 depending on context */
   OMX_U32 nProfileIndex; /**< Used to query for individual profile support information */
} OMX_AUDIO_PARAM_ANDROID_PROFILETYPE;

typedef struct OMX_AUDIO_CONFIG_ANDROID_AUDIOPRESENTATION {
    OMX_U32 nSize;/**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;/**< OMX specification version information */
    OMX_S32 nPresentationId;/**< presentation id */
    OMX_S32 nProgramId;/**< program id */
} OMX_AUDIO_CONFIG_ANDROID_AUDIOPRESENTATION;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_AudioExt_h */
/* File EOF */
