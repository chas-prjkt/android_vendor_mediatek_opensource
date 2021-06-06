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

#ifndef CUSTOM_CFG_FILE_LID_H
#define CUSTOM_CFG_FILE_LID_H

#include "CFG_file_lid.h"

/* the definition of file LID */
typedef enum
{
    AP_CFG_RDCL_FILE_AUDIO_LID=AP_CFG_CUSTOM_BEGIN_LID,	//AP_CFG_CUSTOM_BEGIN_LID: this lid must not be changed, it is reserved for system.
    AP_CFG_CUSTOM_FILE_GPS_LID,
    AP_CFG_RDCL_FILE_AUDIO_COMPFLT_LID,
    AP_CFG_RDCL_FILE_AUDIO_EFFECT_LID,
    AP_CFG_RDEB_FILE_WIFI_LID,
    AP_CFG_RDEB_WIFI_CUSTOM_LID,
    AP_CFG_RDCL_FILE_AUDIO_PARAM_MED_LID,
    AP_CFG_RDCL_FILE_AUDIO_VOLUME_CUSTOM_LID,
    AP_CFG_RDCL_FILE_DUAL_MIC_CUSTOM_LID,
    AP_CFG_RDCL_FILE_AUDIO_WB_PARAM_LID,
    AP_CFG_REEB_PRODUCT_INFO_LID,
//	  AP_CFG_RDCL_FILE_META_LID,
//    AP_CFG_CUSTOM_FILE_CUSTOM1_LID,
//    AP_CFG_CUSTOM_FILE_CUSTOM2_LID,
    AP_CFG_RDCL_FILE_HEADPHONE_COMPFLT_LID,
    AP_CFG_RDCL_FILE_AUDIO_GAIN_TABLE_LID,
    AP_CFG_RDCL_FILE_AUDIO_VER1_VOLUME_CUSTOM_LID,
    AP_CFG_RDCL_FILE_AUDIO_HD_REC_PAR_LID,
    AP_CFG_RDCL_FILE_AUDIO_HD_REC_SCENE_LID,
    AP_CFG_RDCL_FILE_AUDIO_BUFFER_DC_CALIBRATION_PAR_LID,
    AP_CFG_RDCL_FILE_VIBSPK_COMPFLT_LID,
    AP_CFG_RDCL_FILE_AUDIO_MUSIC_DRC_LID,
    AP_CFG_RDCL_FILE_AUDIO_RINGTONE_DRC_LID,
    AP_CFG_RDCL_FILE_AUDIO_MAGI_CONFERENCE_LID,
    AP_CFG_RDCL_FILE_AUDIO_HAC_PARAM_LID,
    AP_CFG_RDCL_FILE_AUDIO_SPEECH_LPBK_PARAM_LID,
    AP_CFG_RDCL_FILE_AUDIO_BT_GAIN_CUSTOM_LID,
    AP_CFG_RDCL_FILE_AUDIO_FUNC_SWITCH_PARAM_LID,
    AP_CFG_CUSTOM_FILE_MAX_LID,
} CUSTOM_CFG_FILE_LID;


/* verno of data items */
/* audio file version */
#define AP_CFG_RDCL_FILE_AUDIO_LID_VERNO			"001"

/* GPS file version */
#define AP_CFG_CUSTOM_FILE_GPS_LID_VERNO			"000"

/* audio acf file version */
#define AP_CFG_RDCL_FILE_AUDIO_COMPFLT_LID_VERNO	"001"

/* audio hcf file version */
#define AP_CFG_RDCL_FILE_HEADPHONE_COMPFLT_LID_VERNO	"001"
/* audio vibspk hcf file version */
#define AP_CFG_RDCL_FILE_VIBSPK_COMPFLT_LID_VERNO	"001"

/* audio effect file version */
#define AP_CFG_RDCL_FILE_AUDIO_EFFECT_LID_VERNO	"001"

/* audio med file version */
#define AP_CFG_RDCL_FILE_AUDIO_PARAM_MED_LID_VERNO  "001"

/* audio volume custom file version */
#define AP_CFG_RDCL_FILE_AUDIO_VOLUME_CUSTOM_LID_VERNO  "001"
#define AP_CFG_RDCL_FILE_AUDIO_VER1_VOLUME_CUSTOM_LID_VERNO  "001"

/* dual mic custom file version */
#define AP_CFG_RDCL_FILE_DUAL_MIC_CUSTOM_LID_VERNO  "002"

/* audio wb specch param custom file version */
#define AP_CFG_RDCL_FILE_AUDIO_WB_PARAM_LID_VERNO "001"

/* audio gain table custom file version */
#define AP_CFG_RDCL_FILE_AUDIO_GAIN_TABLE_LID_VERNO "001"

/* audio hd record par custom file version*/
#define AP_CFG_RDCL_FILE_AUDIO_HD_REC_PAR_LID_VERNO "001"
#define AP_CFG_RDCL_FILE_AUDIO_HD_REC_SCENE_LID_VERNO "001"

/* audio buffer dc calibration custom file version*/
#define AP_CFG_RDCL_FILE_AUDIO_BUFFER_DC_CALIBRATION_PAR_LID_VERNO "000"

/* META log and com port config file version */
#define AP_CFG_RDCL_FILE_META_LID_VERNO			    "000"

/* custom2 file version */
#define AP_CFG_CUSTOM_FILE_CUSTOM1_LID_VERNO			"000"
/* custom2 file version */
#define AP_CFG_CUSTOM_FILE_CUSTOM2_LID_VERNO			"000"

/* WIFI file version */
#define AP_CFG_RDEB_FILE_WIFI_LID_VERNO				"000"
/* WIFI MAC addr file version */
#define AP_CFG_RDCL_FILE_WIFI_ADDR_LID_VERNO		"000"
#define AP_CFG_RDEB_WIFI_CUSTOM_LID_VERNO				"000"
#define AP_CFG_REEB_PRODUCT_INFO_LID_VERNO      "000"

#define AP_CFG_RDCL_FILE_AUDIO_MUSIC_DRC_LID_VERNO			"000"
#define AP_CFG_RDCL_FILE_AUDIO_RINGTONE_DRC_LID_VERNO			"000"

#define AP_CFG_RDCL_FILE_AUDIO_MAGI_CONFERENCE_LID_VERNO			"000"
#define AP_CFG_RDCL_FILE_AUDIO_HAC_PARAM_LID_VERNO			"000"
#define AP_CFG_RDCL_FILE_AUDIO_SPEECH_LPBK_PARAM_LID_VERNO			"000"
#define AP_CFG_RDCL_FILE_AUDIO_BT_GAIN_CUSTOM_LID_VERNO			"000"
#define AP_CFG_RDCL_FILE_AUDIO_FUNC_SWITCH_PARAM_LID_VERNO			"000"

#endif /* CFG_FILE_LID_H */
