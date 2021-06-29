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

#ifndef AUDIO_FFT_TYPES_H
#define AUDIO_FFT_TYPES_H

/*******************************************************************************
 * Include header files
 *******************************************************************************/
/*******************************************************************************
 * Compile Option
 *******************************************************************************/

/*******************************************************************************
 * Base Address Definition
 *******************************************************************************/

/*******************************************************************************
 * Public Function Declaration
 *******************************************************************************/
typedef enum {fft_false, fft_true} kal_bool;
typedef signed char  kal_int8;
typedef unsigned char  kal_uint8;
typedef signed short  kal_int16;
typedef unsigned short  kal_uint16;
typedef signed int    kal_int32;
typedef unsigned int  kal_uint32;

#endif /*AUDIO_FFT_H*/
