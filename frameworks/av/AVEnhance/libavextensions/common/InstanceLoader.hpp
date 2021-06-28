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

#include <dlfcn.h>
#include <common/CommonBase.h>

namespace android {

/*
 * Create vendor objects (which is a subclass of type T)
 * when VENDOR_LIB exists and does contain 'createVendorInstance'
 * Else create the object of type T
 */
template <typename T>
T *InstanceLoader<T>::createInstance(const char *createVendorInstance) {
    ALOGV("createVendorIntance %s", createVendorInstance);
#ifdef MTK_AV_ENHANCEMENTS
    if (!mLib) {
        mLib = ::dlopen(VENDOR_LIB, RTLD_LAZY);
        if (!mLib) {
            ALOGE("createInstance %s", dlerror());
            return new T;
        }
    }

    funPtr func = (funPtr)dlsym(mLib, createVendorInstance);
    if (func) {
        ALOGD("createInstance(%lubit): %s success!", (unsigned long)sizeof(intptr_t)*8, createVendorInstance);
        return reinterpret_cast<T *>((*func)());
    }
#endif
    return new T;
}


// static
template <typename T>
void *InstanceLoader<T>::mLib = NULL;

}  // namespace android
