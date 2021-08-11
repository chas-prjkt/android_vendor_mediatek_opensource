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

#ifndef MC_ROOTID_H_
#define MC_ROOTID_H_

#ifdef WIN32
#define _UNUSED
#else
#define _UNUSED __attribute__((unused))
#endif

/** Root Identifier type. */
typedef uint32_t mcRootid_t;

/** Reserved root id value 1. */
static _UNUSED const mcRootid_t MC_ROOTID_RESERVED1 = 0;

/** Reserved root id value 2. */
static _UNUSED const mcRootid_t MC_ROOTID_RESERVED2 = 0xFFFFFFFF;

/** Root id for system applications. */
static _UNUSED const mcRootid_t MC_ROOTID_SYSTEM = 0xFFFFFFFE;

/** Yet another test ROOT ID */
static _UNUSED const mcRootid_t MC_ROOTID_RESERVED3 = 0xFFFFFFFD;

/** GP TAs - used in the Trusted storage */
static _UNUSED const mcRootid_t MC_ROOTID_GP = 0xFFFFFFFC;

/** RTM's Root ID */
static _UNUSED const mcRootid_t MC_ROOTID_RTM = 0xFFFFFFFB;

#endif // MC_ROOTID_H_
