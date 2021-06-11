LOCAL_PATH := $(call my-dir)

BUILD_AUTOBT_TOOL := true
ifeq ($(BUILD_AUTOBT_TOOL), true)
###########################################################################
# BT HW TEST LIBRARY
###########################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  bt_hw_test.c

LOCAL_MODULE := libbluetooth_hw_test
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := liblog libcutils libdl
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

###########################################################################
# AUTO BT HW TEST TOOL
###########################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  autobt.c

LOCAL_SHARED_LIBRARIES := liblog libcutils libbluetooth_hw_test libbluetooth_relayer

LOCAL_MODULE := autobt
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
include $(BUILD_EXECUTABLE)

endif
