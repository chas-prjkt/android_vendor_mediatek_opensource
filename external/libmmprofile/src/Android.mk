LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES = \
    mmprofile.c

LOCAL_C_INCLUDES := \
    vendor/mediatek/opensource/external/libmmprofile

LOCAL_MODULE := libmmprofile
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

LOCAL_SHARED_LIBRARIES := libcutils liblog
LOCAL_HEADER_LIBRARIES := libhardware_headers
include $(BUILD_SHARED_LIBRARY)
