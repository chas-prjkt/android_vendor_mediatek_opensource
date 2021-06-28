LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    com_mediatek_ap15_drm_RecoveryOmaDrm.cpp

LOCAL_C_INCLUDES += \
    $(base)/drm/libdrmframework/include \
    $(base)/drm/libdrmframework/plugins/common/include \
    $(base)/drm/libdrmframework/plugins/common/util/include \
    $(base)/include \
    $(TOP)/frameworks/native/include \
    $(JNI_H_INCLUDE) \
    bionic \
    external/libxml2/include \
    $(LOCAL_PATH)/include \
    vendor/mediatek/opensource/external/nvram/libnvram \
    vendor/mediatek/opensource/external/nvram/nvram_agent_binder \
    vendor/mediatek/opensource/external/nvram/nvramagentclient \
    vendor/mediatek/opensource/frameworks/av/libdrm/common/mtkutil/include \
    vendor/mediatek/opensource/frameworks/av/drm/include/drm

LOCAL_SHARED_LIBRARIES := \
    libandroid_runtime \
    libdrmframework \
    libutils \
    libdrmmtkutil \
    libcrypto \
    libnativehelper \
    libbinder \
    libdl \
    libcutils

LOCAL_MODULE:= librecoveryomadrm_jni
LOCAL_MODULE_OWNER := mtk

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
