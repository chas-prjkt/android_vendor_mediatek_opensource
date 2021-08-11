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

#ifndef __GP_OPERATIONS_H__
#define __GP_OPERATIONS_H__

#include <algorithm>
#include <mutex>
#include <vector>

#include "tee_client_api.h"

namespace trustonic {

// Keep internal track of operations, to properly deal with cancellation
class TEECOngoingOperations {
    static const uint32_t ENDED = 0xf;
    std::mutex operation_id_counter_mutex_;
    uint32_t operation_id_counter_ = 0x421;
    // List management
    std::mutex mutex_;
    std::vector<TEEC_Operation*> ongoing_operations_;
    std::vector<TEEC_Operation*> cancelled_operations_;
    // Manage a 28-bit counter for operation IDs
    uint32_t getOperationId() {
        std::lock_guard<std::mutex> lock(operation_id_counter_mutex_);
        operation_id_counter_++;
        if (!(operation_id_counter_ & 0xfffffff)) {
            operation_id_counter_ = 1;
        }
        return operation_id_counter_;
    }

public:
    bool start(TEEC_Operation* operation) {
        LOG_D("operation %p start", operation);
        std::lock_guard<std::mutex> lock(mutex_);
        // Check for early cancellation
        auto it = std::find(cancelled_operations_.begin(), cancelled_operations_.end(),
                            operation);
        if (it != cancelled_operations_.end()) {
            LOG_I("operation cancelled before start");
            cancelled_operations_.erase(it);
            return false;
        }

        auto operation_id = getOperationId();
        // Leave space for status bits below operation ID
        operation->started = operation_id << 4;
        LOG_D("operation %p (ID %u) started", operation, operation_id);
        ongoing_operations_.push_back(operation);
        return true;
    }

    void end(TEEC_Operation* operation) {
        LOG_D("operation %p end", operation);
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = std::find(ongoing_operations_.begin(), ongoing_operations_.end(),
                            operation);
        if (it == ongoing_operations_.end()) {
            LOG_E("operation %p not ongoing, cannot end", operation);
            return;
        }
        ongoing_operations_.erase(it);
        operation->started = ENDED;
        LOG_D("operation %p ended", operation);
    }

    bool cancel(TEEC_Operation* operation) {
        LOG_D("operation %p cancel", operation);
        std::lock_guard<std::mutex> lock(mutex_);
        // Look in list first in case started field was reset by client
        auto it = std::find(ongoing_operations_.begin(), ongoing_operations_.end(),
                            operation);
        if (it != ongoing_operations_.end()) {
            LOG_D("operation %p ongoing, request cancellation", operation);
            return true;
        }

        if (operation->started == 0) {
            // Operation not started yet, add to cancelled
            auto it = std::find(cancelled_operations_.begin(), cancelled_operations_.end(),
                                operation);
            if (it == cancelled_operations_.end()) {
                cancelled_operations_.push_back(operation);
                LOG_D("operation %p cancellation recorded", operation);
            } else {
                LOG_D("operation %p cancellation was already recorded", operation);
            }
        } else {
            LOG_I("operation ended before cancellation");
        }

        return false;
    }
};

}

#endif // __GP_OPERATIONS_H__
