LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= calibration_tool.c

LOCAL_MODULE:= cal_tool
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

LOCAL_SHARED_LIBRARIES := libutils libcutils libhwm

include $(BUILD_EXECUTABLE)
