LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

CAL_CFLAGS := -Wall-ansi

LOCAL_SRC_FILES := bperf_util.c common.c main.c

LOCAL_MODULE:= picus
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_CLASS := EXECUTABLES

include $(BUILD_EXECUTABLE)
