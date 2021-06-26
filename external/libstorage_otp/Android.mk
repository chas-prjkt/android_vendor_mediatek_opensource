LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libstorage_otp
LOCAL_SHARED_LIBRARIES:= libc libcutils libbase liblog

LOCAL_SRC_FILES:= storage_otp.c
LOCAL_SRC_FILES += ufs.cpp
LOCAL_SRC_FILES += emmc.cpp

LOCAL_C_INCLUDES += system/core/include/private
LOCAL_C_INCLUDES += system/core/fs_mgr/include_fstab/fstab

LOCAL_STATIC_LIBRARIES += libfstab
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
