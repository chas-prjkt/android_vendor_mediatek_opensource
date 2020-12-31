LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MTK_ROOT_PATH :=  vendor/mediatek/opensource

LOCAL_SRC_FILES:= \
    MTKPrimaryDevicesHalClientInterface.cpp \
    MTKPrimaryDevicesHalClientImpl.cpp \
    ConversionHelperHidl.cpp \
    HalDeathHandlerHidl.cpp \
    MTKDeviceHalHidl.cpp \
    MTKDevicesFactoryHalHidl.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    liblog \
    libutils \
    libbase \
    libhwbinder \
    libhidlbase \
    android.hardware.audio@5.0 \
    android.hardware.audio.common@5.0 \
    android.hardware.audio.common@5.0-util \
    libmedia_helper \
    libbinder

LOCAL_HEADER_LIBRARIES += libaudioclient_headers libaudio_system_headers libmedia_headers
LOCAL_STATIC_LIBRARIES := \

LOCAL_C_INCLUDES:= \
    $(MTK_ROOT_PATH)/hardware/audio/common/include \
    frameworks/av/include

LOCAL_MODULE:= libaudioprimarydevicehalifclient
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)
