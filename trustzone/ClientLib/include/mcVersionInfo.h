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

#ifndef MCVERSIONINFO_H_
#define MCVERSIONINFO_H_

/** Length of MobiCore product ID string. */
#define MC_PRODUCT_ID_LEN 64

/** Global MobiCore Version Information.
 */
typedef struct {
    char productId[MC_PRODUCT_ID_LEN]; /** < Product ID of Mobicore; zero-terminated */
    uint32_t versionMci;               /** < Version of Mobicore Control Interface */
    uint32_t versionSo;                /** < Version of Secure Objects */
    uint32_t versionMclf;              /** < Version of MobiCore Load Format */
    uint32_t versionContainer;         /** < Version of MobiCore Container Format */
    uint32_t versionMcConfig;          /** < Version of MobiCore Configuration Block Format */
    uint32_t versionTlApi;             /** < Version of MobiCore Trustlet API Implementation */
    uint32_t versionDrApi;             /** < Version of MobiCore Driver API Implementation */
    uint32_t versionCmp;               /** < Version of Content Management Protocol */
} mcVersionInfo_t;

#endif /** MCVERSIONINFO_H_ */
