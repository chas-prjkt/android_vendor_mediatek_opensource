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
#include <dlfcn.h>
#include <linux/input.h>
#include <sys/resource.h>
#include <cutils/properties.h>
#include <log/log.h>
#include "ta_log.h"
#include <string.h>
#include <signal.h>
#include <errno.h>



#define LIB_FULL_NAME "libthermalalgo.so"

#define UNUSED(x)    if(x){}

int (*libthermal_algo_setup)(void ) = NULL;

void loadlib()
{
	void *handle;

	handle = dlopen(LIB_FULL_NAME, RTLD_NOW);
	if (handle == NULL) {
		TALOG_ERROR("Can't load library: %s", dlerror());
		goto fail_out;
	}

	if ((libthermal_algo_setup = (int (*)(void))dlsym(handle, "libthermal_algo_setup")) == NULL) {
		TALOG_ERROR("load 'libthermal_algo_setup' error: %s", dlerror());
		goto close_handle;
	}
	return;

close_handle:
	dlclose(handle);
fail_out:
	return;
}


int main(int argc, char *argv[])
{
        UNUSED(argc);
        UNUSED(argv);

	TALOG_INFO("ta_main\n");
	loadlib();

	if(libthermal_algo_setup){
		libthermal_algo_setup();
	}


	return 0;
}
