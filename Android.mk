ifeq ($(TARGET_PROVIDES_MTK_PROPRIETARY),true)

MTK_ROOT_PATH := $(call my-dir)

# MTK Proprietary
include $(call all-makefiles-under, $(MTK_ROOT_PATH))

endif # TARGET_PROVIDES_MTK_PROPRIETARY
