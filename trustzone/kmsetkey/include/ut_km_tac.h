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

#ifndef __UT_KM_TAC_H__
#define __UT_KM_TAC_H__

__BEGIN_DECLS


int ut_km_import_google_key(unsigned char *data, unsigned int datalen);
int ut_km_check_google_key(void);

__END_DECLS
#endif //__UT_KM_SETKEY_H__
