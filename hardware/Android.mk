MTK_HARD_ROOT_PATH := $(call my-dir)

# MTK Audio
include $(MTK_HARD_ROOT_PATH)/audio/common/service/5.0/Android.mk
include $(MTK_HARD_ROOT_PATH)/audio/common/client/Android.mk

# MTK Power
include $(MTK_HARD_ROOT_PATH)/power/service/Power/1.3/Android.mk
