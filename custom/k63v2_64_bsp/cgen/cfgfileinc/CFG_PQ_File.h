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

#ifndef _CFG_PQ_FILE_H
#define _CFG_PQ_FILE_H

typedef struct {
	unsigned int gamma_id;
	unsigned int gamma_lut[257]; /* gamma table 10bit*3*512  */
	unsigned int gamma_gain[15];
	unsigned int gamma_checksum; /* for check gamma lut correct or not */
	unsigned int pq_reserved[64];
} PQ_CUSTOM_LUT;

#define CFG_FILE_PQ_CUSTOM_REC_SIZE    sizeof(PQ_CUSTOM_LUT)
#define CFG_FILE_PQ_CUSTOM_REC_TOTAL   1

#endif
