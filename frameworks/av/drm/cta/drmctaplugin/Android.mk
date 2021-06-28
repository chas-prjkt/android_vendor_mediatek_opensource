LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

base := $(TOP)/frameworks/av

LOCAL_SRC_FILES:= \
    src/DrmCtaPlugIn.cpp

LOCAL_MODULE := libdrmctaplugin
LOCAL_MODULE_OWNER := mtk
LOCAL_SYSTEM_EXT_MODULE := true

LOCAL_C_INCLUDES += \
    $(base)/drm/libdrmframework/include \
    $(base)/drm/libdrmframework/plugins/common/include \
    $(base)/drm/libdrmframework/plugins/common/util/include \
    $(base)/include \
    vendor/mediatek/opensource/native/include \
    vendor/mediatek/opensource/frameworks/av/drm/include \
    vendor/mediatek/opensource/frameworks/av/drm/common/mtkutil/include \
    vendor/mediatek/opensource/frameworks/av/drm/common/mtkutil/cta \
    $(LOCAL_PATH)/include \
    external/libxml2/include \
    bionic \
    system/core/base/include

LOCAL_SHARED_LIBRARIES := \
    libandroidicu \
    libutils \
    libcutils \
    liblog \
    libdl \
    libandroid_runtime \
    libdrmmtkutil \
    libcrypto\
    libssl\
    libbinder

LOCAL_STATIC_LIBRARIES := \
    libdrmframeworkcommon \
    libxml2

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_RELATIVE_PATH := drm/cta

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
