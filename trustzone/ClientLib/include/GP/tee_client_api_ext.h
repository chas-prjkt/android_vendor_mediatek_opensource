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

#ifndef   __TEE_CLIENT_API_EXT_H__
#define   __TEE_CLIENT_API_EXT_H__

#if TBASE_API_LEVEL >= 9

#pragma GCC visibility push(default)

/*
 * Registers two contexts which are platform-specific, such the virtual machine
 * and the application in an Android-based environment.
 */
TEEC_EXPORT void TEEC_TT_RegisterPlatformContext(
    void                *globalContext,
    void                *localContext);

#pragma GCC visibility pop

#endif /* TBASE_API_LEVEL >= 9 */

#endif /* __TEE_CLIENT_API_EXT_H__ */
