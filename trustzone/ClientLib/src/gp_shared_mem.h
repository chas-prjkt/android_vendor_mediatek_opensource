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

#ifndef __GP_SHARED_MEM_H__
#define __GP_SHARED_MEM_H__

#include <algorithm>
#include <mutex>
#include <vector>

#include <sys/mman.h>

#include "tee_client_api.h"

namespace trustonic {

// Keep internal track of allocated shared memories
class TEECAllocatedSharedMemories {
    std::mutex shared_mems_mutex_;
    std::vector<TEEC_SharedMemory> shared_mems_;
public:
    bool allocate(TEEC_SharedMemory* shared_mem) {
        // Allocate memory (use size 1 if 0 given)
        size_t size = shared_mem->size;
        if (!size) {
            size++;
        }

        shared_mem->buffer = ::mmap(0, size, PROT_READ | PROT_WRITE,
                                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (shared_mem->buffer == MAP_FAILED) {
            shared_mem->buffer = nullptr;
            return false;
        }

        std::lock_guard<std::mutex> lock(shared_mems_mutex_);
        shared_mems_.push_back(*shared_mem);
        LOG_D("allocated shared mem, size %zu", shared_mems_.size());
        return true;
    }

    bool free(TEEC_SharedMemory* shared_mem) {
        std::lock_guard<std::mutex> lock(shared_mems_mutex_);
        auto it = std::find_if(shared_mems_.begin(), shared_mems_.end(),
        [shared_mem](const TEEC_SharedMemory& other) {
            return shared_mem->buffer == other.buffer;
        });
        if (it == shared_mems_.end()) {
            LOG_D("shared mem not found");
            return false;
        }

        // Free allocated memory (use size 1 if 0 given)
        size_t size = shared_mem->size;
        if (!size) {
            size++;
        }

        ::munmap(shared_mem->buffer, size);
        shared_mem->buffer = nullptr;
        shared_mem->size = 0;
        shared_mems_.erase(it);
        LOG_D("freed shared mem, size %zu", shared_mems_.size());
        return true;
    }
};

}

#endif // __GP_SHARED_MEM_H__
