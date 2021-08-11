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

#ifndef MC_SUID_H_
#define MC_SUID_H_

/** Length of SUID. */
#define MC_SUID_LEN    16

/** Platform specific device identifier (serial number of the chip). */
typedef struct {
    uint8_t data[MC_SUID_LEN - sizeof(uint32_t)];
} suidData_t;

/** Soc unique identifier type. */
typedef struct {
    uint32_t    sipId;  /**< Silicon Provider ID to be set during build. */
    suidData_t  suidData;
} mcSuid_t;

#endif // MC_SUID_H_
