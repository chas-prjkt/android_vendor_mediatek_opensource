LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -DMTK_ECCCI_C2K

LOCAL_SRC_FILES := ccci_lib.c

LOCAL_SHARED_LIBRARIES := libdl libm libc++ libc liblog
LOCAL_STATIC_LIBRARIES := libcutils

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/platform

LOCAL_EXPORT_C_INCLUDE_DIRS := \
	$(LOCAL_PATH)/include \

LOCAL_SRC_FILES += platform/ccci_lib_platform.c

LOCAL_MODULE := libccci_util
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

LOCAL_MODULE_TAGS := optional
include $(call all-makefiles-under,$(LOCAL_PATH))
include $(BUILD_SHARED_LIBRARY)
