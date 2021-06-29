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

#define LOG_TAG "ion_cs"

#include "utils/CallStack.h"
#include "ion_ulit.h"
#include <stdlib.h>
#include <string>
#include <log/log.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"  {
#endif

#define ION_PROC1_NAME "_All_"
#define ION_PROC2_NAME "No_Process"

void dumping_callstack(const char *func_name, int ion_fd, int share_fd)
{
	if (strstr("_All_", ION_PROC1_NAME))
		android::CallStack cs("ion_cs");
	else if ((strstr(getprogname(), ION_PROC1_NAME)) || (strstr(getprogname(), ION_PROC2_NAME)))
		android::CallStack cs("ion_cs");
	ALOGE("proc %s func %s ion_fd %d, share fd %d!\n", getprogname(), func_name, ion_fd, share_fd);
}

#ifdef __cplusplus
}
#endif
