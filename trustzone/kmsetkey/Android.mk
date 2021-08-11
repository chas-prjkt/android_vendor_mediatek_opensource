LOCAL_PATH    := $(call my-dir)

include $(CLEAR_VARS)

# Add new source files here
LOCAL_SRC_FILES +=\
    ut_km_ioctl.cpp \
    ut_km_tac.cpp \
    ut_kmsetkey.cpp

LOCAL_C_INCLUDES +=\
    $(LOCAL_PATH)/include \
    external/openssl/include \
    hardware/libhardware/include \
    system/core/include \
    vendor/mediatek/opensource/trustzone/imsg_log/include \
    vendor/mediatek/opensource/trustzone/ClientLib/include/GP

LOCAL_CFLAGS := -DANDROID_CHANGES -Werror
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_RELATIVE_PATH := hw

PLATFORM_VERSION_MAJOR := $(word 1,$(subst .,$(space),$(PLATFORM_VERSION)))
LOCAL_CFLAGS+=-DPLATFORM_VERSION_MAJOR=$(PLATFORM_VERSION_MAJOR)

LOCAL_SHARED_LIBRARIES := libimsg_log libTEECommon liblog
LOCAL_MODULE := kmsetkey.beanpod
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES +=\
    ut_km_ioctl.cpp \
    ut_km_tac.cpp \
    ut_kmsetkey.cpp

LOCAL_C_INCLUDES +=\
    $(LOCAL_PATH)/include \
    external/openssl/include \
    hardware/libhardware/include \
    system/core/include \
    vendor/mediatek/opensource/trustzone/imsg_log/include \
    vendor/mediatek/opensource/trustzone/ClientLib/include/GP

LOCAL_CFLAGS := -DANDROID_CHANGES -Werror
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_RELATIVE_PATH := hw

PLATFORM_VERSION_MAJOR := $(word 1,$(subst .,$(space),$(PLATFORM_VERSION)))
LOCAL_CFLAGS+=-DPLATFORM_VERSION_MAJOR=$(PLATFORM_VERSION_MAJOR)
LOCAL_SHARED_LIBRARIES := libimsg_log libTEECommon liblog
LOCAL_MODULE := kmsetkey.default
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := bp_kmsetkey_ca
LOCAL_INIT_RC := microtrust.bp_kmsetkey_ca.rc

LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
    kmsetkey_ca.cpp

LOCAL_C_INCLUDES:= \
    $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES := \
    libdl \
		libhardware \
		libcutils \
		liblog \
		libutils

LOCAL_CFLAGS := -Wall -Werror -g
LOCAL_LDFLAGS := -Wl,--unresolved-symbols=ignore-all

include $(BUILD_EXECUTABLE)
