LOCAL_PATH:= $(call my-dir)

#
# Impl shared lib
#
include $(CLEAR_VARS)
LOCAL_MODULE := vendor.mediatek.hardware.nvram@1.0-impl
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_SRC_FILES := \
    Nvram.cpp

LOCAL_C_INCLUDES += \
	vendor/mediatek/opensource/external/nvram/libnvram

LOCAL_SHARED_LIBRARIES := \
    libbase \
    libcutils \
    libhardware \
    libhidlbase \
    libhidltransport \
    liblog \
    libutils \
    libnvram \
    libfile_op \
    vendor.mediatek.hardware.nvram@1.0

include $(BUILD_SHARED_LIBRARY)

#
# register the hidl service
#
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    service.cpp

LOCAL_C_INCLUDES += \
	vendor/mediatek/opensource/external/nvram/libnvram

ifeq ($(strip $(MTK_INTERNAL_LOG_ENABLE)),yes)
    LOCAL_CFLAGS += -DMTK_INTERNAL_LOG_ENABLE
endif

LOCAL_SHARED_LIBRARIES := \
  libdl \
  libutils \
  libcutils \
  libhardware \
  libhidlbase \
  libhidltransport \
  libbinder \
  libnvram \
  liblog \
  vendor.mediatek.hardware.nvram@1.0 \

LOCAL_MODULE:= vendor.mediatek.hardware.nvram@1.0-service
LOCAL_INIT_RC := vendor.mediatek.hardware.nvram@1.0-sevice.rc
LOCAL_MODULE_TAGS := optional
LOCAL_CPPFLAGS += -fexceptions
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_OWNER := mtk
include $(BUILD_EXECUTABLE)
