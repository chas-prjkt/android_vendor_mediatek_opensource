LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES:= libc libcutils libnvram libcustom_nvram liblog
LOCAL_SRC_FILES:= \
	libfile_op.c

LOCAL_C_INCLUDES:=\
	vendor/mediatek/opensource/external/nvram/libnvram \
	vendor/mediatek/opensource/external/nvram/libfile_op \
  system/core/include/private

LOCAL_MODULE:=libfile_op
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE:= false
include $(BUILD_SHARED_LIBRARY)
