LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libhwm.c
LOCAL_MODULE := libhwm
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_SHARED_LIBRARIES += libnvram liblog libfile_op

LOCAL_C_INCLUDES := \
      $(LOCAL_PATH)/include \
      $vendor/mediatek/opensource/external/audio_utils/common_headers/cgen \
	    vendor/mediatek/opensource/external/nvram/libfile_op \
	    vendor/mediatek/opensource/custom/common/cgen/cfgfileinc \
	    vendor/mediatek/opensource/custom/common/cgen/cfgdefault \
	    vendor/mediatek/opensource/custom/common/cgen/inc \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgfileinc \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgdefault \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc

LOCAL_HEADER_LIBRARIES := \
	libnvram_headers \
	libfile_op_headers

LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)/include

ifneq (,$(filter $(strip $(TARGET_BOARD_PLATFORM)), mt6797 mt6799 mt8163 mt8167 mt8173))
    LOCAL_CFLAGS += -DSUPPORT_SENSOR_ACCESS_NVRAM
endif

include $(BUILD_SHARED_LIBRARY)
