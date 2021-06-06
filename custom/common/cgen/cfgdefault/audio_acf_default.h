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

#ifndef AUDIO_ACF_DEFAULT_H
#define AUDIO_ACF_DEFAULT_H
/* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
#define BES_LOUDNESS_ACF_L_HPF_FC       400
#define BES_LOUDNESS_ACF_L_HPF_ORDER    2
#define BES_LOUDNESS_ACF_L_BPF_FC       4000, 500, 2000, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_L_BPF_BW       1421, 284, 1421, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_L_BPF_GAIN     1536, -1536, 1536, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_L_LPF_FC       0
#define BES_LOUDNESS_ACF_L_LPF_ORDER    0
#define BES_LOUDNESS_ACF_R_HPF_FC       400
#define BES_LOUDNESS_ACF_R_HPF_ORDER    2
#define BES_LOUDNESS_ACF_R_BPF_FC       4000, 500, 2000, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_R_BPF_BW       1421, 284, 1421, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_R_BPF_GAIN     1536, -1536, 1536, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_R_LPF_FC       0
#define BES_LOUDNESS_ACF_R_LPF_ORDER    0

#define BES_LOUDNESS_ACF_SEP_LR_FILTER  0

#define BES_LOUDNESS_ACF_WS_GAIN_MAX    0
#define BES_LOUDNESS_ACF_WS_GAIN_MIN    0
#define BES_LOUDNESS_ACF_FILTER_FIRST   0

#define BES_LOUDNESS_ACF_NUM_BANDS      0
#define BES_LOUDNESS_ACF_FLT_BANK_ORDER 0
#define BES_LOUDNESS_ACF_DRC_DELAY      0
#define BES_LOUDNESS_ACF_CROSSOVER_FREQ 0, 0, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_SB_MODE        0, 0, 0, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_SB_GAIN        0, 0, 0, 0, 0, 0, 0, 0
#define BES_LOUDNESS_ACF_GAIN_MAP_IN    \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0}
#define BES_LOUDNESS_ACF_GAIN_MAP_OUT   \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0},                  \
        {0, 0, 0, 0, 0}
#define BES_LOUDNESS_ACF_ATT_TIME       \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0}
#define BES_LOUDNESS_ACF_REL_TIME       \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0}
#define BES_LOUDNESS_ACF_HYST_TH        \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0},               \
        {0, 0, 0, 0, 0, 0}

#define BES_LOUDNESS_ACF_LIM_TH     0
#define BES_LOUDNESS_ACF_LIM_GN     0
#define BES_LOUDNESS_ACF_LIM_CONST  0
#define BES_LOUDNESS_ACF_LIM_DELAY  0

#endif
