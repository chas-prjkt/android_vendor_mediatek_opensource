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

#define LOG_TAG "mtkaudiohalservice"
#define LOG_NDEBUG 0

#include <android/hardware/audio/5.0/IDevicesFactory.h>
#include <android/hardware/audio/effect/5.0/IEffectsFactory.h>
#include <android/hardware/bluetooth/a2dp/1.0/IBluetoothAudioOffload.h>
#include <android/hardware/bluetooth/audio/2.0/IBluetoothAudioProvidersFactory.h>
#include <android/hardware/soundtrigger/2.2/ISoundTriggerHw.h>
#include <binder/ProcessState.h>
#include <cutils/properties.h>
#include <hidl/HidlTransportSupport.h>
#include <hidl/LegacySupport.h>
#include <hwbinder/ProcessState.h>

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::hardware::registerPassthroughServiceImplementation;

using android::hardware::audio::effect::V5_0::IEffectsFactory;
using android::hardware::audio::V5_0::IDevicesFactory;
using android::hardware::soundtrigger::V2_2::ISoundTriggerHw;
using android::hardware::registerPassthroughServiceImplementation;

using namespace android::hardware;
using android::OK;

#define SUPPORT_AUDIO_DEVICES_FACTORY
#define SUPPORT_AUDIO_EFFECTS_FACTORY
#define SUPPORT_SOUNDTRIGGER_HW

#ifdef FORCE_DIRECTCOREDUMP
#include <sys/prctl.h>
#define SIGNUM 7
void directcoredump_init() {
    int sigtype[SIGNUM] = {SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV, SIGTRAP, SIGSYS};
    char value[PROPERTY_VALUE_MAX] = {'\0'};

    // eng&userdebug load direct-coredump default enable
    // user load direct-coredump default disable due to libdirect-coredump.so will not be preloaded
    property_get("persist.vendor.aee.core.direct", value, "default");
    if (strncmp(value, "disable", sizeof("disable"))) {
        int loop;
        for (loop = 0; loop < SIGNUM; loop++) {
            signal(sigtype[loop], SIG_DFL);
        }
    }
}
#endif

/** Try to register the provided factories in the provided order.
 *  If any registers successfully, do not register any other and return true.
 *  If all fail, return false.
 */
template <class... Factories>
bool registerPassthroughServiceImplementations() {
    return ((registerPassthroughServiceImplementation<Factories>() != OK) && ...);
}

int main(int /* argc */, char * /* argv */ []) {
    ALOGD("Start audiohalservice");

    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

#ifdef FORCE_DIRECTCOREDUMP
    directcoredump_init();
    if (prctl(PR_SET_DUMPABLE, 1) < 0) {
        ALOGD("audiohalservice set dumpable fail");
    }
#endif
    ::android::ProcessState::initWithDriver("/dev/vndbinder");
    // start a threadpool for vndbinder interactions
    ::android::ProcessState::self()->startThreadPool();

    const int32_t defaultValue = -1;
    int32_t value =
        property_get_int32("persist.vendor.audio.service.hwbinder.size_kbyte", defaultValue);
    if (value != defaultValue) {
        ALOGD("Configuring hwbinder with mmap size %d KBytes", value);
        ProcessState::initWithMmapSize(static_cast<size_t>(value) * 1024);
    }
    configureRpcThreadpool(16, true /*callerWillJoin*/);

    // Keep versions on a separate line for easier parsing
    // clang-format off
    LOG_ALWAYS_FATAL_IF((registerPassthroughServiceImplementations<
                                audio::V5_0::IDevicesFactory>()),
                        "Could not register audio core API");

    LOG_ALWAYS_FATAL_IF((registerPassthroughServiceImplementations<
                                audio::effect::V5_0::IEffectsFactory>()),
                        "Could not register audio effect API");
    // clang-format on

    ALOGW_IF((registerPassthroughServiceImplementations<soundtrigger::V2_2::ISoundTriggerHw>()),
             "Could not register soundtrigger API");

    ALOGW_IF(registerPassthroughServiceImplementations<
                     bluetooth::audio::V2_0::IBluetoothAudioProvidersFactory>(),
             "Could not register Bluetooth audio API");

    // remove the old HIDL when Bluetooth Audio Hal V2 has offloading supported
    ALOGW_IF(registerPassthroughServiceImplementations<
                     bluetooth::a2dp::V1_0::IBluetoothAudioOffload>(),
             "Could not register Bluetooth audio offload API");

    joinRpcThreadpool();
}
