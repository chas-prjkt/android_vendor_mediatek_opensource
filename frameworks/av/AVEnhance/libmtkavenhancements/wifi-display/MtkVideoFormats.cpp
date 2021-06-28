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

//#define LOG_NDEBUG 0
#define LOG_TAG "MtkVideoFormats"
#include <utils/Log.h>

#include "MtkVideoFormats.h"

#include <media/stagefright/foundation/ADebug.h>

///M: Support portrait-resolution
#include <cutils/properties.h>
#include <stdlib.h>

namespace android
{


// static
const MtkVideoFormats::config_t MtkVideoFormats::mResolutionTable[][32] = {
    {
        // CEA Resolutions
        { 640, 480, 60, false, 0, 0},
        { 720, 480, 60, false, 0, 0},
        { 720, 480, 60, true, 0, 0},
        { 720, 576, 50, false, 0, 0},
        { 720, 576, 50, true, 0, 0},
        { 1280, 720, 30, false, 0, 0},
        { 1280, 720, 60, false, 0, 0},
        { 1920, 1080, 30, false, 0, 0},
        { 1920, 1080, 60, false, 0, 0},
        { 1920, 1080, 60, true, 0, 0},
        { 1280, 720, 25, false, 0, 0},
        { 1280, 720, 50, false, 0, 0},
        { 1920, 1080, 25, false, 0, 0},
        { 1920, 1080, 50, false, 0, 0},
        { 1920, 1080, 50, true, 0, 0},
        { 1280, 720, 24, false, 0, 0},
        { 1920, 1080, 24, false, 0, 0},
        { 720, 1280, 30, false, 0, 0}, //index:17, 720p Portrait WFD support
        { 1080, 1920, 30, false, 0, 0}, //index: 18, 1080p Portrait WFD support
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
    },
    {
        // VESA Resolutions
        { 800, 600, 30, false, 0, 0},
        { 800, 600, 60, false, 0, 0},
        { 1024, 768, 30, false, 0, 0},
        { 1024, 768, 60, false, 0, 0},
        { 1152, 864, 30, false, 0, 0},
        { 1152, 864, 60, false, 0, 0},
        { 1280, 768, 30, false, 0, 0},
        { 1280, 768, 60, false, 0, 0},
        { 1280, 800, 30, false, 0, 0},
        { 1280, 800, 60, false, 0, 0},
        { 1360, 768, 30, false, 0, 0},
        { 1360, 768, 60, false, 0, 0},
        { 1366, 768, 30, false, 0, 0},
        { 1366, 768, 60, false, 0, 0},
        { 1280, 1024, 30, false, 0, 0},
        { 1280, 1024, 60, false, 0, 0},
        { 1400, 1050, 30, false, 0, 0},
        { 1400, 1050, 60, false, 0, 0},
        { 1440, 900, 30, false, 0, 0},
        { 1440, 900, 60, false, 0, 0},
        { 1600, 900, 30, false, 0, 0},
        { 1600, 900, 60, false, 0, 0},
        { 1600, 1200, 30, false, 0, 0},
        { 1600, 1200, 60, false, 0, 0},
        { 1680, 1024, 30, false, 0, 0},
        { 1680, 1024, 60, false, 0, 0},
        { 1680, 1050, 30, false, 0, 0},
        { 1680, 1050, 60, false, 0, 0},
        { 1920, 1200, 30, false, 0, 0},
        { 1920, 1200, 60, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
    },
    {
        // HH Resolutions
        { 800, 480, 30, false, 0, 0},
        { 800, 480, 60, false, 0, 0},
        { 854, 480, 30, false, 0, 0},
        { 854, 480, 60, false, 0, 0},
        { 864, 480, 30, false, 0, 0},
        { 864, 480, 60, false, 0, 0},
        { 640, 360, 30, false, 0, 0},
        { 640, 360, 60, false, 0, 0},
        { 960, 540, 30, false, 0, 0},
        { 960, 540, 60, false, 0, 0},
        { 848, 480, 30, false, 0, 0},
        { 848, 480, 60, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
        { 0, 0, 0, false, 0, 0},
    }
};

MtkVideoFormats::MtkVideoFormats()
{
    memcpy(mConfigs, mResolutionTable, sizeof(mConfigs));

    for(size_t i = 0; i < kNumResolutionTypes; ++i) {
        mResolutionEnabled[i] = 0;
    }

    setNativeResolution(RESOLUTION_CEA, 0);  // default to 640x480 p60
}

void MtkVideoFormats::setNativeResolution(ResolutionType type, size_t index)
{
    CHECK_LT(type, kNumResolutionTypes);
    CHECK(GetConfiguration(type, index, NULL, NULL, NULL, NULL));

    mNativeType = type;
    mNativeIndex = index;

    setResolutionEnabled(type, index);
}

void MtkVideoFormats::getNativeResolution(
    ResolutionType *type, size_t *index) const
{
    *type = mNativeType;
    *index = mNativeIndex;
}

void MtkVideoFormats::disableAll()
{
    for(size_t i = 0; i < kNumResolutionTypes; ++i) {
        mResolutionEnabled[i] = 0;

        for(size_t j = 0; j < 32; j++) {
            mConfigs[i][j].profile = mConfigs[i][j].level = 0;
        }
    }
}

void MtkVideoFormats::enableAll()
{
    for(size_t i = 0; i < kNumResolutionTypes; ++i) {
        mResolutionEnabled[i] = 0xffffffff;

        for(size_t j = 0; j < 32; j++) {
            mConfigs[i][j].profile = (1ul << PROFILE_CBP);
            mConfigs[i][j].level = (1ul << LEVEL_31);
        }
    }
}

void MtkVideoFormats::enableResolutionUpto(
    ResolutionType type, size_t index,
    ProfileType profile, LevelType level)
{
    size_t width, height, fps, score;
    bool interlaced;

    if(!GetConfiguration(type, index, &width, &height,
                         &fps, &interlaced)) {
        ALOGE("Maximum resolution not found!");
        return;
    }

    score = width * height * fps * (!interlaced + 1);

    for(size_t i = 0; i < kNumResolutionTypes; ++i) {
        for(size_t j = 0; j < 32; j++) {
            if(GetConfiguration((ResolutionType)i, j,
                                &width, &height, &fps, &interlaced)
                    && score >= width * height * fps * (!interlaced + 1)) {
                ///M: Support portrait-resolution
                if(width < height) {
                    continue;
                }

                setResolutionEnabled((ResolutionType)i, j);
                setProfileLevel((ResolutionType)i, j, profile, level);
            }
        }
    }
}

void MtkVideoFormats::setResolutionEnabled(
    ResolutionType type, size_t index, bool enabled)
{
    CHECK_LT(type, kNumResolutionTypes);
    CHECK(GetConfiguration(type, index, NULL, NULL, NULL, NULL));

    if(enabled) {
        mResolutionEnabled[type] |= (1ul << index);
        mConfigs[type][index].profile = (1ul << PROFILE_CBP);
        mConfigs[type][index].level = (1ul << LEVEL_31);
    } else {
        mResolutionEnabled[type] &= ~(1ul << index);
        mConfigs[type][index].profile = 0;
        mConfigs[type][index].level = 0;
    }
}

void MtkVideoFormats::setProfileLevel(
    ResolutionType type, size_t index,
    ProfileType profile, LevelType level)
{
    CHECK_LT(type, kNumResolutionTypes);
    CHECK(GetConfiguration(type, index, NULL, NULL, NULL, NULL));

    mConfigs[type][index].profile = (1ul << profile);
    mConfigs[type][index].level = (1ul << level);
}

void MtkVideoFormats::getProfileLevel(
    ResolutionType type, size_t index,
    ProfileType *profile, LevelType *level) const
{
    CHECK_LT(type, kNumResolutionTypes);
    CHECK(GetConfiguration(type, index, NULL, NULL, NULL, NULL));

    int i, bestProfile = -1, bestLevel = -1;

    for(i = 0; i < kNumProfileTypes; ++i) {
        if(mConfigs[type][index].profile & (1ul << i)) {
            bestProfile = i;
        }
    }

    for(i = 0; i < kNumLevelTypes; ++i) {
        if(mConfigs[type][index].level & (1ul << i)) {
            bestLevel = i;
        }
    }

    if(bestProfile == -1 || bestLevel == -1) {
        ALOGE("Profile or level not set for resolution type %d, index %zu",
              type, index);
        bestProfile = PROFILE_CBP;
        bestLevel = LEVEL_31;
    }

    *profile = (ProfileType) bestProfile;
    *level = (LevelType) bestLevel;
}

bool MtkVideoFormats::isResolutionEnabled(
    ResolutionType type, size_t index) const
{
    CHECK_LT(type, kNumResolutionTypes);
    CHECK(GetConfiguration(type, index, NULL, NULL, NULL, NULL));

    return mResolutionEnabled[type] & (1ul << index);
}

// static
bool MtkVideoFormats::GetConfiguration(
    ResolutionType type,
    size_t index,
    size_t *width, size_t *height, size_t *framesPerSecond,
    bool *interlaced)
{
    CHECK_LT(type, kNumResolutionTypes);

    if(index >= 32) {
        return false;
    }

    const config_t *config = &mResolutionTable[type][index];

    if(config->width == 0) {
        return false;
    }

    if(width) {
        *width = config->width;
    }

    if(height) {
        *height = config->height;
    }

    if(framesPerSecond) {
        *framesPerSecond = config->framesPerSecond;
    }

    if(interlaced) {
        *interlaced = config->interlaced;
    }

    return true;
}

bool MtkVideoFormats::parseH264Codec(const char *spec)
{
    unsigned profile, level, res[3];

    if(sscanf(
                spec,
                "%02x %02x %08X %08X %08X",
                &profile,
                &level,
                &res[0],
                &res[1],
                &res[2]) != 5) {
        return false;
    }

    for(size_t i = 0; i < kNumResolutionTypes; ++i) {
        for(size_t j = 0; j < 32; ++j) {
            if(res[i] & (1ul << j)) {
                mResolutionEnabled[i] |= (1ul << j);

                if(profile > mConfigs[i][j].profile) {
                    // prefer higher profile (even if level is lower)
                    mConfigs[i][j].profile = profile;
                    mConfigs[i][j].level = level;
                } else if(profile == mConfigs[i][j].profile &&
                          level > mConfigs[i][j].level) {
                    mConfigs[i][j].level = level;
                }
            }
        }
    }

    return true;
}

// static
bool MtkVideoFormats::GetProfileLevel(
    ProfileType profile, LevelType level, unsigned *profileIdc,
    unsigned *levelIdc, unsigned *constraintSet)
{
    CHECK_LT(profile, kNumProfileTypes);
    CHECK_LT(level, kNumLevelTypes);

    static const unsigned kProfileIDC[kNumProfileTypes] = {
        66,     // PROFILE_CBP
        100,    // PROFILE_CHP
    };

    static const unsigned kLevelIDC[kNumLevelTypes] = {
        31,     // LEVEL_31
        32,     // LEVEL_32
        40,     // LEVEL_40
        41,     // LEVEL_41
        42,     // LEVEL_42
    };

    static const unsigned kConstraintSet[kNumProfileTypes] = {
        0xc0,   // PROFILE_CBP
        0x0c,   // PROFILE_CHP
    };

    if(profileIdc) {
        *profileIdc = kProfileIDC[profile];
    }

    if(levelIdc) {
        *levelIdc = kLevelIDC[level];
    }

    if(constraintSet) {
        *constraintSet = kConstraintSet[profile];
    }

    return true;
}

bool MtkVideoFormats::parseFormatSpec(const char *spec)
{
    CHECK_EQ(kNumResolutionTypes, 3);

    disableAll();

    unsigned native, dummy;
    size_t size = strlen(spec);
    size_t offset = 0;

    if(sscanf(spec, "%02x %02x ", &native, &dummy) != 2) {
        return false;
    }

    offset += 6; // skip native and preferred-display-mode-supported
    CHECK_LE(offset + 58, size);

    while(offset < size) {
        parseH264Codec(spec + offset);
        offset += 60; // skip H.264-codec + ", "
    }

    mNativeIndex = native >> 3;
    mNativeType = (ResolutionType)(native & 7);

    bool success;

    if(mNativeType >= kNumResolutionTypes) {
        success = false;
    } else {
        success = GetConfiguration(
                      mNativeType, mNativeIndex, NULL, NULL, NULL, NULL);
    }

    if(!success) {
        ALOGW("sink advertised an illegal native resolution, fortunately "
              "this value is ignored for the time being...");
    }

    return true;
}

AString MtkVideoFormats::getFormatSpec(bool forM4Message) const
{
    CHECK_EQ(kNumResolutionTypes, 3);

    // wfd_video_formats:
    // 1 byte "native"
    // 1 byte "preferred-display-mode-supported" 0 or 1
    // one or more avc codec structures
    //   1 byte profile
    //   1 byte level
    //   4 byte CEA mask
    //   4 byte VESA mask
    //   4 byte HH mask
    //   1 byte latency
    //   2 byte min-slice-slice
    //   2 byte slice-enc-params
    //   1 byte framerate-control-support
    //   max-hres (none or 2 byte)
    //   max-vres (none or 2 byte)
#ifdef MTK_WFD_SINK_SUPPORT

    if(!forM4Message) {
        AString sp               = " ";
        AString comma            = ",";

        AString native           ="00";    // Index to CEA resolution/refresh rates
        AString prfr_dsp_mod_supt= "00";     // Not supported
        AString fst_profile      = "02";         // CHP(Constrained High Profile)
        AString fst_level        = "10";         // H.264 Level 4.2
        AString fst_cea_support  = "0001FFFF";   /* support all */
        AString fst_vesa_support = "0F3FFFFF";   /* support all except for 1600x1200p30/p60 & 1920x1200p30/p60 */
        AString fst_hh_support   = "00000FFF";   /* support all */

        AString fst_latency              = "00";
        AString fst_min_slice_size       = "0000";
        AString fst_slice_enc_params     = "0000";
        /* as per to the WFD testplan, the frame skipping interval should be set to 500 ms */
        AString fst_frm_rate_ctl_supt    = "13";         // Frame skipping support, max time-interval 2s

        AString fst_max_hres             = "none";
        AString fst_max_vres             = "none";

        AString fst_misc_params;

        ///M: Support portrait-resolution
        char portrait[PROPERTY_VALUE_MAX];

        if(property_get("media.wfd.portrait", portrait, NULL)) {
            int value = atoi(portrait);

            if(value == 1) {
                ALOGI("media.wfd.portrait:%s", portrait);
                fst_cea_support = "0007FFFF";    /* support all + portrait */
            }
        }

        fst_misc_params.append(fst_cea_support);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_vesa_support);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_hh_support);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_latency);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_min_slice_size);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_slice_enc_params);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_frm_rate_ctl_supt);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_max_hres);
        fst_misc_params.append(sp);
        fst_misc_params.append(fst_max_vres);


        AString fst_format_list;
        fst_format_list.append("02 ");
        fst_format_list.append("10 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("02 ");
        fst_format_list.append("08 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("02 ");
        fst_format_list.append("04 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("02 ");
        fst_format_list.append("02 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("02 ");
        fst_format_list.append("01 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("01 ");
        fst_format_list.append("10 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("01 ");
        fst_format_list.append("08 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("01 ");
        fst_format_list.append("04 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("01 ");
        fst_format_list.append("02 ");
        fst_format_list.append(fst_misc_params);
        fst_format_list.append(comma);

        fst_format_list.append(sp);
        fst_format_list.append("01 ");
        fst_format_list.append("01 ");
        fst_format_list.append(fst_misc_params);


        AString reply;
        reply.append(native);
        reply.append(sp);
        reply.append(prfr_dsp_mod_supt);
        reply.append(sp);
        reply.append(fst_format_list);


        return reply;
    }



#endif
    return AStringPrintf(
               "%02x 00 %02x %02x %08x %08x %08x 00 0000 0000 00 none none",
               forM4Message ? 0x00 : ((mNativeIndex << 3) | mNativeType),
               mConfigs[mNativeType][mNativeIndex].profile,
               mConfigs[mNativeType][mNativeIndex].level,
               mResolutionEnabled[0],
               mResolutionEnabled[1],
               mResolutionEnabled[2]);
}

// static
bool MtkVideoFormats::PickBestFormat(
    const MtkVideoFormats &sinkSupported,
    const MtkVideoFormats &sourceSupported,
    ResolutionType *chosenType,
    size_t *chosenIndex,
    ProfileType *chosenProfile,
    LevelType *chosenLevel)
{
#if 0
    // Support for the native format is a great idea, the spec includes
    // these features, but nobody supports it and the tests don't validate it.

    ResolutionType nativeType;
    size_t nativeIndex;
    sinkSupported.getNativeResolution(&nativeType, &nativeIndex);

    if(sinkSupported.isResolutionEnabled(nativeType, nativeIndex)) {
        if(sourceSupported.isResolutionEnabled(nativeType, nativeIndex)) {
            ALOGI("Choosing sink's native resolution");
            *chosenType = nativeType;
            *chosenIndex = nativeIndex;
            return true;
        }
    } else {
        ALOGW("Sink advertised native resolution that it doesn't "
              "actually support... ignoring");
    }

    sourceSupported.getNativeResolution(&nativeType, &nativeIndex);

    if(sourceSupported.isResolutionEnabled(nativeType, nativeIndex)) {
        if(sinkSupported.isResolutionEnabled(nativeType, nativeIndex)) {
            ALOGI("Choosing source's native resolution");
            *chosenType = nativeType;
            *chosenIndex = nativeIndex;
            return true;
        }
    } else {
        ALOGW("Source advertised native resolution that it doesn't "
              "actually support... ignoring");
    }

#endif

    bool first = true;
    uint32_t bestScore = 0;
    size_t bestType = 0;
    size_t bestIndex = 0;

    for(size_t i = 0; i < kNumResolutionTypes; ++i) {
        for(size_t j = 0; j < 32; ++j) {
            size_t width, height, framesPerSecond;
            bool interlaced;

            if(!GetConfiguration(
                        (ResolutionType)i,
                        j,
                        &width, &height, &framesPerSecond, &interlaced)) {
                break;
            }

            if(!sinkSupported.isResolutionEnabled((ResolutionType)i, j)
                    || !sourceSupported.isResolutionEnabled(
                        (ResolutionType)i, j)) {
                continue;
            }

            ALOGV("type %zu, index %zu, %zu x %zu %c%zu supported",
                  i, j, width, height, interlaced ? 'i' : 'p', framesPerSecond);

            uint32_t score = width * height * framesPerSecond;

            if(!interlaced) {
                score *= 2;
            }

            ///M: Support portrait-resolution
            if(width < height) {
                score *= 4;
            }

            if(first || score > bestScore) {
                bestScore = score;
                bestType = i;
                bestIndex = j;

                first = false;
            }
        }
    }

    if(first) {
        return false;
    }

    *chosenType = (ResolutionType)bestType;
    *chosenIndex = bestIndex;

    // Pick the best profile/level supported by both sink and source.
    ProfileType srcProfile, sinkProfile;
    LevelType srcLevel, sinkLevel;
    sourceSupported.getProfileLevel(
        (ResolutionType)bestType, bestIndex,
        &srcProfile, &srcLevel);
    sinkSupported.getProfileLevel(
        (ResolutionType)bestType, bestIndex,
        &sinkProfile, &sinkLevel);
    *chosenProfile = srcProfile < sinkProfile ? srcProfile : sinkProfile;
    *chosenLevel = srcLevel < sinkLevel ? srcLevel : sinkLevel;

    return true;
}

}  // namespace android
