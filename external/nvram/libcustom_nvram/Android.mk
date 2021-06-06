LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

# tEMP
LOCAL_CFLAGS += -D__MTK_DUAL_MIC_SUPPORT__
LOCAL_CFLAGS += -D__NXP_SMARTPA_SUPPORT__
LOCAL_CFLAGS += -DMTK_ECCCI_C2K
LOCAL_CFLAGS += -DMTK_ECCCI_C2K
LOCAL_CFLAGS += -DMTK_EMMC_SUPPORT
LOCAL_CFLAGS += -DMTK_UFS_SUPPORT

LOCAL_SHARED_LIBRARIES:= libc libcutils liblog
LOCAL_SRC_FILES:= \
      CFG_file_info.c

LOCAL_C_INCLUDES:= \
      vendor/mediatek/opensource/external/nvram/libnvram \
      vendor/mediatek/opensource/external/nvram/libfile_op \
      vendor/mediatek/opensource/external/audio_utils/common_headers/cgen/cfgfileinc \
      vendor/mediatek/opensource/external/audio_utils/common_headers/cgen \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen \
	    vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc \
	    vendor/mediatek/opensource/custom/common/cgen \
	    vendor/mediatek/opensource/custom/common/cgen/inc

LOCAL_MODULE:=libcustom_nvram
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
