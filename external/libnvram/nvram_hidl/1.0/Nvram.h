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

#ifndef VENDOR_MEDIATEK_HARDWARE_NVRAM_V1_0_NVRAM_H
#define VENDOR_MEDIATEK_HARDWARE_NVRAM_V1_0_NVRAM_H

#include <vendor/mediatek/hardware/nvram/1.0/INvram.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor {
namespace mediatek {
namespace hardware {
namespace nvram {
namespace V1_0 {
namespace implementation {

using ::android::hidl::base::V1_0::DebugInfo;
using ::android::hidl::base::V1_0::IBase;
using ::vendor::mediatek::hardware::nvram::V1_0::INvram;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Nvram : public INvram {
    // Methods from ::vendor::mediatek::hardware::nvram::V1_0::INvram follow.
    Return<void> readFileByName(const hidl_string& filename, uint32_t size, readFileByName_cb _hidl_cb) override;
    Return<int8_t> writeFileByNamevec(const hidl_string& filename, uint32_t size, const hidl_vec<uint8_t>& data) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

extern "C" INvram* HIDL_FETCH_INvram(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace nvram
}  // namespace hardware
}  // namespace mediatek
}  // namespace vendor

#endif  // VENDOR_MEDIATEK_HARDWARE_NVRAM_V1_0_NVRAM_H
