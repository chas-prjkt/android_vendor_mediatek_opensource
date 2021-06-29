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

#ifndef AUDIO_FFT_H
#define AUDIO_FFT_H

/*******************************************************************************
 * Include header files
 *******************************************************************************/
#include "DIF_FFT.h"
#include <stdbool.h>

#include "math.h"

/*******************************************************************************
 * Compile Option
 *******************************************************************************/

/*******************************************************************************
 * Base Address Definition
 *******************************************************************************/

/*******************************************************************************
 * Public Function Declaration
 *******************************************************************************/

kal_bool ApplyFFT256(kal_uint32 samplerate,short *pData, kal_uint16 u2DataStart, kal_uint32* u4FreqData, kal_uint32* u4MaxData);
kal_bool FreqCheck(kal_uint32 u4TargetFreq, kal_uint32 u4FreqData);
kal_bool MagnitudeCheck(kal_uint32 u4LboundMag, kal_uint32 u4UboundMag, kal_uint32* u4MagData);
kal_bool ApplyFFT(kal_uint32 samplerate,short *pData, kal_uint16 u2DataStart, Complex *pComData, kal_uint32 *u4FreqData, kal_uint32 *u4MaxData);
int comp_divs(Complex *rst, const Complex z, const float eps);
#endif /*AUDIO_FFT_H*/
