LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MTK_ROOT_PATH :=  vendor/mediatek/opensource

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

LOCAL_C_INCLUDES += \
    $(MTK_ROOT_PATH)/hardware/power/include \

LOCAL_SHARED_LIBRARIES := liblog \
    libutils \
    libhidlbase \
    android.hardware.power@1.0 \
    android.hardware.power@1.1 \
    android.hardware.power@1.2 \
    vendor.mediatek.hardware.power@2.0 \
    vendor.mediatek.hardware.power@2.1 \
    vendor.mediatek.hardware.mtkpower@1.0

LOCAL_SRC_FILES := power_hal_wrap.cpp
LOCAL_MODULE := libpowerhalwrap_vendor
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

LOCAL_C_INCLUDES += \
    $(MTK_ROOT_PATH)/hardware/power/include \

LOCAL_SHARED_LIBRARIES := liblog \
    libutils \
    libhidlbase \
    android.hardware.power@1.0 \
    android.hardware.power@1.1 \
    android.hardware.power@1.2 \
    vendor.mediatek.hardware.power@2.0 \
    vendor.mediatek.hardware.power@2.1 \
    vendor.mediatek.hardware.mtkpower@1.0

LOCAL_SRC_FILES := power_hal_wrap.cpp
LOCAL_MODULE := libpowerhalwrap
LOCAL_MODULE_OWNER := mtk

include $(BUILD_SHARED_LIBRARY)
