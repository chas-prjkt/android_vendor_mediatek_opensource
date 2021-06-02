LOCAL_CLANG := true
MY_PATH := vendor/mediatek/opensource

LOCAL_CFLAGS := -DLOG_TAG=\"DynamicFpsPolicy\"
LOCAL_CFLAGS += -Wall -Werror -Wunused -Wunreachable-code

LOCAL_C_INCLUDES:= \
	$(MY_PATH)/hardware/libdfps/inc

LOCAL_SRC_FILES := \
	utils.cpp \
	FpsPolicy.cpp \
	FpsInfo.cpp \
	FpsVsync.cpp \
	string_def.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	liblog \
	libhidlbase \
	libhidltransport \
	libhwbinder \
	libhardware

LOCAL_EXPORT_C_INCLUDE_DIRS := \
  $(LOCAL_PATH)/../../inc
