LOCAL_PATH := $(call my-dir)

ifeq ($(MTK_WAPI_SUPPORT), yes)
include $(CLEAR_VARS)
LOCAL_MODULE := libwapi
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SHARED_LIBRARIES_64 := libkeystore-wifi-hidl libcrypto liblog libc++ libc libm libdl
LOCAL_MULTILIB := 64
LOCAL_SRC_FILES_64 := arm64/libwapi.so
include $(BUILD_PREBUILT)
endif

ifeq ($(MTK_WAPI_SUPPORT), yes)
include $(CLEAR_VARS)
LOCAL_MODULE := libwapi
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SHARED_LIBRARIES := libkeystore-wifi-hidl libcrypto liblog libc++ libc libm libdl
LOCAL_MULTILIB := 32
LOCAL_SRC_FILES_32 := arm/libwapi.so
include $(BUILD_PREBUILT)
endif
