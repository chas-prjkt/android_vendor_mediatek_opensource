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

#ifndef _DIF_FFT
#define _DIF_FFT
typedef struct complex_
{
    float  real;
    float  image;
} Complex;

typedef struct complex_fixed_
{
    short  real;
    short  image;
} Complex_Fixed;

typedef struct complex_fixed_32_
{
    int  real;
    int  image;
} Complex_Fixed_32;

void DIF_FFT(Complex x[],unsigned int); // floating point version

void DIF_FFT_Fix16(Complex_Fixed C_z[], unsigned int Nu, short* Shift_of_C_z); // 16 bit fixed point version, Nu has to be 8

void DIF_FFT_Fix32(Complex_Fixed_32 C_z[], unsigned int Nu, short* Shift_of_C_z); // 32 bit fixed point version, Nu has to be 8

#define Max_Q (16-14) //

#include "stdio.h"
extern 	FILE* DeNoised_PCM;

#endif
