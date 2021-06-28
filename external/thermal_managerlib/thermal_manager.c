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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cutils/properties.h>
#include <android/log.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <dlfcn.h>
#include <log/log.h>


#define MTK_LOG_ENABLE	(1)
#define TM_LOG_TAG "thermal_mgr"

#if MTK_LOG_ENABLE
#define TM_LOG(_priority_, _fmt_, args...)  LOG_PRI(_priority_, TM_LOG_TAG, _fmt_, ##args)

#else
#define TM_LOG(_priority_, _fmt_, args...)
#endif

int (*loadmtc)(char *) = NULL;
//#define LIB_FULL_NAME "libmtcloader.so"
#define LIB_FULL_NAME "/vendor/lib/libmtcloader.so"
typedef int (*load)(char *);

int (*loadchange_policy)(char *, int) = NULL;
typedef int (*load_change_policy)(char *, int);

int main(int argc, char **argv)
{
    int i = 0;
    void *handle, *func, *func2;

    TM_LOG(ANDROID_LOG_INFO, "%s argc %d.\n", __func__, argc);
    for (; i < argc; i++) {
        TM_LOG(ANDROID_LOG_INFO, "argv[%d] %s.\n", i, argv[i]);
    }

    handle = dlopen(LIB_FULL_NAME, RTLD_NOW);
    /* TM_LOG(ANDROID_LOG_INFO, "dlopen.\n"); */
	if (handle == NULL) {
		TM_LOG(ANDROID_LOG_ERROR, "fails to load lib err: %s.\n", dlerror());
		return -1;
	}

	func = dlsym(handle, "loadmtc");
	loadmtc = (load)func;

	if (loadmtc == NULL) {
        TM_LOG(ANDROID_LOG_ERROR, "loadmtc err: %s.\n", dlerror());
		dlclose(handle);
		return -1;
	}

    if (argc - 1 > 0) {
        int ret = 0;

        if (argc == 2) {
            TM_LOG(ANDROID_LOG_INFO, "loadmtc %s\n", argv[1]);
            ret = loadmtc(argv[1]);
        } else if (argc == 3) {
  	    func2 = dlsym(handle, "change_policy");
  	    loadchange_policy = (load_change_policy)func2;

    	    if (loadchange_policy == NULL) {
                TM_LOG(ANDROID_LOG_ERROR, "change_policy err: %s.\n", dlerror());
    		dlclose(handle);
    		return -1;
    	    }
    	    ret = loadchange_policy(argv[1], atoi(argv[2]));
            TM_LOG(ANDROID_LOG_INFO, "change_policy ret: %d.\n", ret);
 	}
	dlclose(handle);
        return ret;
    } else {
        TM_LOG(ANDROID_LOG_INFO, "loadmtc thermal.conf\n");
        int ret = loadmtc("/vendor/etc/.tp/thermal.conf"); /* default policy */
        dlclose(handle);
        return ret;
    }
}
