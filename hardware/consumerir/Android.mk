LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := hardware/libhardware_legacy/include \
                    hardware/libhardware/include \
                    $(LOCAL_PATH)/include \

LOCAL_HEADER_LIBRARIES += libsystem_headers
LOCAL_MODULE := consumerir.$(TARGET_BOARD_PLATFORM)
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_SRC_FILES := src/consumerir.c
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := both

include $(BUILD_SHARED_LIBRARY)
