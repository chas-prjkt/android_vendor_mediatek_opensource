LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= thermal
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MULTILIB := first

LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= \
    thermal.c

LOCAL_C_INCLUDES = \
    $(LOCAL_PATH)/ \
    hardware/libhardware_legacy/include \
    hardware/libhardware/include \
    vendor/mediatek/opensource/hardware/ccci/include \
    vendor/mediatek/opensource/system/netdagent/include

LOCAL_INIT_RC := init.thermal.rc
LOCAL_SHARED_LIBRARIES := libcutils libc libifcutils_mtk libdl liblog

include $(BUILD_EXECUTABLE)
