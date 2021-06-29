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

#ifndef __MMPROFILE_FUNCTION_H__
#define __MMPROFILE_FUNCTION_H__

#include <linux/mmprofile_internal.h>

MMP_Event MMProfileRegisterEvent(MMP_Event parent, const char *name);
MMP_Event MMProfileFindEvent(MMP_Event parent, const char *name);
void MMProfileEnableEvent(MMP_Event event, long enable);
void MMProfileEnableFTraceEvent(MMP_Event event, long enable, long ftrace);
void MMProfileEnableEventRecursive(MMP_Event event, long enable);
void MMProfileEnableFTraceEventRecursive(MMP_Event event, long enable, long ftrace);
long MMProfileQueryEnable(MMP_Event event);
void MMProfileLog(MMP_Event event, MMP_LogType type);
void MMProfileLogEx(MMP_Event event, MMP_LogType type, unsigned long data1, unsigned long data2);
long MMProfileLogMeta(MMP_Event event, MMP_LogType type, MMP_MetaData_t *pMetaData);
long MMProfileLogMetaString(MMP_Event event, MMP_LogType type, const char *str);
long MMProfileLogMetaStringEx(MMP_Event event, MMP_LogType type, unsigned long data1, unsigned long data2, const char *str);
long MMProfileLogMetaStructure(MMP_Event event, MMP_LogType type, MMP_MetaDataStructure_t *pMetaData);
long MMProfileLogMetaBitmap(MMP_Event event, MMP_LogType type, MMP_MetaDataBitmap_t *pMetaData);

#define MMProfileLogStructure(event, type, pStruct, struct_type) \
{ \
    MMP_MetaDataStructure_t MetaData; \
    MetaData.data1 = 0; \
    MetaData.data2 = 0; \
    strcpy(MetaData.struct_name, #struct_type); \
    MetaData.struct_size = sizeof(struct_type); \
    MetaData.pData = (void *)(pStruct); \
    MMProfileLogMetaStructure(event, type, &MetaData); \
}

#endif
