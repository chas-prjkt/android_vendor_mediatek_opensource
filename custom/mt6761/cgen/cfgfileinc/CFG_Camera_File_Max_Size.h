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

#ifndef __CFG_CAMERA_FILE_MAX_SIZE_H__
#define __CFG_CAMERA_FILE_MAX_SIZE_H__

#define MAXIMUM_NVRAM_CAMERA_DEFECT_FILE_SIZE      (5120) //BYTE 81920

#define MAXIMUM_NVRAM_CAMERA_ISP_FILE_SIZE         (1039536) // 640K byte (621796 byte )
//#define MAXIMUM_NVRAM_CAMERA_ISP_FILE_SIZE         (143360) // 140K bytes = 140*1024 = 143360
#define MAXIMUM_NVRAM_CAMERA_3A_FILE_SIZE          (96500) // 31K bytes
#define MAXIMUM_NVRAM_CAMERA_SENSOR_FILE_SIZE      (4096)
#define MAXIMUM_NVRAM_CAMERA_LENS_FILE_SIZE        (22528*7)
#define MAXIMUM_NVRAM_CAMERA_VERSION_FILE_SIZE     (140)
#define MAXIMUM_NVRAM_CAMERA_FEATURE_FILE_SIZE      (34752+12160+3000*7)
#define MAXIMUM_NVRAM_CAMERA_GEOMETRY_FILE_SIZE     (54000)
#define MAXIMUM_NVRAM_CAMERA_FOV_FILE_SIZE         (80)

#define MAXIMUM_NVRAM_CAMERA_PLINE_FILE_SIZE     (90000)
#define MAXIMUM_NVRAM_CAMERA_SHADING_FILE_SIZE      (90000) //BYTE 81920--> 16000 for meta tool limitation

#define MAXIMUM_NVRAM_CAMERA_AF_FILE_SIZE   (4096)
#define MAXIMUM_NVRAM_CAMERA_FLASH_CALIBRATION_FILE_SIZE   (12800)

#define MAXIMUM_CAMERA_SHADING_SIZE  (1050652)
#define MAXIMUM_CAMERA_PLINE_SIZE  (900000)

#define MAXIMUM_NVRAM_CAMERA_PARA_FILE_SIZE  MAXIMUM_NVRAM_CAMERA_ISP_FILE_SIZE

#endif
