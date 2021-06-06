LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES:= libc libcutils liblog
LOCAL_SRC_FILES:=nvram_platform.c
LOCAL_C_INCLUDES:= \
    vendor/mediatek/opensource/external/nvram/libnvram

LOCAL_MODULE:=libnvram_platform
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE:=false
include $(BUILD_SHARED_LIBRARY)
