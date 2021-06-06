LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.c md_init_fsm.c time_clib_srv.c magic_pattern.c env_setting.c ccci_legacy.c ccci_log.c ccci_support_utils.c

LOCAL_C_INCLUDES := \
	vendor/mediatek/opensource/external/nvram/libnvram \
	vendor/mediatek/ims/include/libsysenv \
	vendor/mediatek/opensource/hardware/ccci/include \
	vendor/mediatek/opensource/external/ccci_mdinit_src/platform \
	vendor/mediatek/opensource/custom/common/cgen/cfgfileinc \
	vendor/mediatek/opensource/custom/common/cgen/cfgdefault \
	vendor/mediatek/opensource/custom/common/cgen/inc \
	vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgfileinc \
	vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/cfgdefault \
	vendor/mediatek/opensource/custom/$(MTK_CUSTOM_PATH)/cgen/inc \
	$(LOCAL_PATH)/platform

LOCAL_SHARED_LIBRARIES := libsysenv libcutils liblog libnvram libccci_util libhardware_legacy libc++ libc libm libdl

LOCAL_CFLAGS += -Werror
LOCAL_MODULE := ccci_mdinit
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MULTILIB := 32

LOCAL_MODULE_TAGS := optional
LOCAL_INIT_RC := init.cccimdinit.rc

include $(call all-makefiles-under,$(LOCAL_PATH))
include $(BUILD_EXECUTABLE)
