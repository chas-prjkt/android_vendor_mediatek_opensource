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

#ifndef _COMMON_BASE_H_
#define _COMMON_BASE_H_

namespace android {

static const char * VENDOR_LIB = "libmtkavenhancements.so";

typedef void *(*funPtr)(void);

template <typename T>
struct InstanceLoader {
    static T *createInstance(const char *createVendorInstance);

private:
    static void *mLib;
};

/*
 * every Factory use this template to create the Factory Instance.
 * get(): pointer to the specific Factory instance.
 */
#define FACTORY_INSTANCE_LOADER(T)  \
protected:                          \
    T();                            \
    virtual ~T();                   \
    static T *sInst;                \
private:                            \
    T(const T&);                    \
    T &operator=(T &);              \
public:                             \
    static T *get() {               \
        return sInst;               \
    }                               \
    friend struct InstanceLoader<T>;

}  // namespace android

#endif  // _COMMON_BASE_H_
