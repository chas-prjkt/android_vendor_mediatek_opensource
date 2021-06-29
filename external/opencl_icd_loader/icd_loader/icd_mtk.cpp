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

#include "icd.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>

static pthread_once_t initialized = PTHREAD_ONCE_INIT;

#ifdef CL_TRACE
	#include <log/log.h>
	#include <cutils/properties.h>

	cl_bool sCLSystraceEnabled = false;
	cl_bool sCLTraceLevel = false;
#endif

/*
 *
 * Vendor enumeration functions
 *
 */

// go through the list of vendors in the two configuration files
void khrIcdOsVendorsEnumerate(void)
{
	const char* libSearchList[] = {
#if defined(__LP64__)
		"/system/lib64/egl/libGLES_mali.so",
		"/system/vendor/lib64/egl/libGLES_mali.so",
		"/system/vendor/lib64/libPVROCL.so",
#else
		"/system/lib/egl/libGLES_mali.so",
		"/system/vendor/lib/egl/libGLES_mali.so",
		"/system/vendor/lib/libPVROCL.so",
#endif
	};

	int i;
	int size = sizeof(libSearchList) / sizeof(libSearchList[0]);

	for (i = 0; i < size; ++i)
		khrIcdVendorAdd(libSearchList[i]);

#ifdef CL_TRACE
	initCLTraceLevel();
#endif

}

// go through the list of vendors only once
void khrIcdOsVendorsEnumerateOnce(void)
{
    pthread_once(&initialized, khrIcdOsVendorsEnumerate);
}

#ifdef CL_TRACE
void initCLTraceLevel()
{
	char value[PROPERTY_VALUE_MAX];
	property_get( "debug.ocl.trace" , value, 0);

	sCLSystraceEnabled = !strcasecmp(value, "systrace");
	if(sCLSystraceEnabled)
	{
		sCLTraceLevel = 0;
		ALOGD("initCLTraceLevel sCLSystraceEnabled = %d\n", sCLSystraceEnabled);
		return;
	}

	int propertyLevel = atoi(value);
	sCLTraceLevel = propertyLevel;
	ALOGD("initCLTraceLevel sCLTraceLevel = %d\n", sCLTraceLevel);
}
#endif

/*
 *
 * Dynamic library loading functions
 *
 */

// dynamically load a library.  returns NULL on failure
void *khrIcdOsLibraryLoad(const char *libraryName)
{
    return dlopen (libraryName, RTLD_NOW);
}

// get a function pointer from a loaded library.  returns NULL on failure.
void *khrIcdOsLibraryGetFunctionAddress(void *library, const char *functionName)
{
    return dlsym(library, functionName);
}

// unload a library
void khrIcdOsLibraryUnload(void *library)
{
    dlclose(library);
}
