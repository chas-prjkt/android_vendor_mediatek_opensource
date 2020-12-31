/*
 * Copyright (C) 2016 The Android Open Source Project
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
/*
    Stub to build x86 binary for Cuttlestone
*/

#include <stdlib.h>

typedef uintptr_t backtrace_frame_t;

#if !defined(UNUSED)
#define UNUSED(x)	((void)(x))
#endif

__attribute__((visibility("default")))
ssize_t libudf_unwind_backtrace(backtrace_frame_t* backtrace, size_t ignore_depth, size_t max_depth)
{
    ssize_t frames = -1;

    UNUSED(backtrace); UNUSED(ignore_depth); UNUSED(max_depth);

    return frames;
}
