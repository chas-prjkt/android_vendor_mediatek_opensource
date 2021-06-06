LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES:= libc libcutils libcustom_nvram liblog

ifeq ($(strip $(MTK_INTERNAL_LOG_ENABLE)),yes)
    LOCAL_CFLAGS += -DMTK_INTERNAL_LOG_ENABLE
endif

LOCAL_SRC_FILES:= \
   	libnvram_sec.c

#	libnvram.c
LOCAL_C_INCLUDES:= \
      vendor/mediatek/opensource/external/nvram/libfile_op \
      vendor/mediatek/opensource/external/nvram/libnvram \
      vendor/mediatek/opensource/custom/common/cgen/inc \
      vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc

LOCAL_MODULE:=libnvram_sec
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE:= false
include $(BUILD_SHARED_LIBRARY)
