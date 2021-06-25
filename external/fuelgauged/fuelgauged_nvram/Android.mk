LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	fgauge_nvram.cpp \
	fg_log.cpp

LOCAL_C_INCLUDES:= \
    vendor/mediatek/opensource/external/nvram/libnvram \
    vendor/mediatek/opensource/custom/common/cgen/cfgfileinc \
    vendor/mediatek/opensource/custom/common/cgen/cfgdefault \
    vendor/mediatek/opensource/custom/common/cgen/inc \
    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgfileinc \
    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgdefault \
    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc

LOCAL_SHARED_LIBRARIES := libcutils libutils libdl libnvram liblog

LOCAL_MODULE:= fuelgauged_nvram
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MULTILIB := 32
LOCAL_INIT_RC := fuelgauged_nvram_init.rc
include $(BUILD_EXECUTABLE)
