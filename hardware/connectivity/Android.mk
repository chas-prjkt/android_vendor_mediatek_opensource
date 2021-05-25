ifeq ($(TARGET_PROVIDES_MTK_OSS_CONNECTIVITY),true)

CONNECTIVITY_PATH := $(call my-dir)

include $(call all-makefiles-under, $(CONNECTIVITY_PATH))

endif # TARGET_PROVIDES_MTK_OSS_CONNECTIVITY
