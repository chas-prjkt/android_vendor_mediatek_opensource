LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := libcutils libnvram liblog
LOCAL_SRC_FILES := libwifitest.c

LOCAL_C_INCLUDES := \
 vendor/mediatek/opensource/external/nvram/libnvram \
 vendor/mediatek/opensource/custom/common/cgen/cfgfileinc \
 vendor/mediatek/opensource/custom/common/cgen/cfgdefault \
 vendor/mediatek/opensource/custom/common/cgen/inc \
 vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgfileinc \
 vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgdefault \
 vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libwifitest
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

BUILD_TEST_APP = false

ifeq ($(BUILD_TEST_APP),true)
  include $(CLEAR_VARS)
  LOCAL_SHARED_LIBRARIES := libnvram libcutils libwifitest
  LOCAL_SRC_FILES := main.c
  LOCAL_CFLAGS += -Wall -Werror
  LOCAL_MODULE := wifitest
  LOCAL_PROPRIETARY_MODULE := true
  LOCAL_MODULE_OWNER := mtk
  LOCAL_MODULE_TAGS := optional
  include $(BUILD_EXECUTABLE)
endif
