/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef __KMSETKEY_H__
#define __KMSETKEY_H__

#define MAX_MSG_SIZE           4096

#ifdef __cplusplus
extern "C" {
#endif

int32_t ree_import_attest_keybox(const uint8_t *peakb, const uint32_t peakb_len, const uint32_t finish);
int32_t ree_check_attest_keybox(const uint8_t *peakb, const uint32_t peakb_len, const uint32_t finish);

#ifdef __cplusplus
}
#endif

#endif /* __KMSETKEY_H__ */
