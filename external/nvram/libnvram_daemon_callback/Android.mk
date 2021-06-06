LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES:= libc liblog libcustom_nvram libnvram
LOCAL_SRC_FILES:= \
      libnvram_daemon_callback.c

LOCAL_C_INCLUDES:= \
      vendor/mediatek/opensource/external/nvram/libfile_op \
      vendor/mediatek/opensource/external/nvram/libnvram \
	    vendor/mediatek/opensource/custom/common/cgen/cfgfileinc \
	    vendor/mediatek/opensource/custom/common/cgen/cfgdefault \
	    vendor/mediatek/opensource/custom/common/cgen/inc \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgfileinc \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgdefault \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc \

LOCAL_MODULE:=libnvram_daemon_callback
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
