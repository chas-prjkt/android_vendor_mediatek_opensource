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

#ifndef MC_SPID_H_
#define MC_SPID_H_

#ifdef WIN32
#define _UNUSED
#else
#define _UNUSED __attribute__((unused))
#endif

/** Service provider Identifier type. */
typedef uint32_t mcSpid_t;

/** SPID value used as free marker in root containers. */
static _UNUSED const mcSpid_t MC_SPID_FREE = 0xFFFFFFFF;

/** Reserved SPID value. */
static _UNUSED const mcSpid_t MC_SPID_RESERVED = 0;

/** SPID for system applications. */
static _UNUSED const mcSpid_t MC_SPID_SYSTEM = 0xFFFFFFFE;

/** SPID reserved for tests only */
static _UNUSED const mcSpid_t MC_SPID_RESERVED_TEST = 0xFFFFFFFD;
static _UNUSED const mcSpid_t MC_SPID_TRUSTONIC_TEST = 0x4;

/** SPID reserved for OTA development */
static _UNUSED const mcSpid_t MC_SPID_TRUSTONIC_OTA = 0x2A;

/** GP TAs - stored in the trusted storage. They all share the same */
static _UNUSED const mcSpid_t MC_SPID_GP = 0xFFFFFFFC;

/** RTM's SPID */
static _UNUSED const mcSpid_t MC_SPID_RTM = 0xFFFFFFFB;

#endif // MC_SPID_H_
