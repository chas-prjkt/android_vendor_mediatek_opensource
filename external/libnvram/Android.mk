LIBNVRAM_PATH := $(call my-dir)

include $(LIBNVRAM_PATH)/libfile_op/Android.mk
include $(LIBNVRAM_PATH)/libnvram_sec/Android.mk

include $(LIBNVRAM_PATH)/$(TARGET_BOARD_PLATFORM)/Android.mk

include $(LIBNVRAM_PATH)/nvram_daemon/Android.mk
include $(LIBNVRAM_PATH)/nvram_hidl/1.1/Android.mk
