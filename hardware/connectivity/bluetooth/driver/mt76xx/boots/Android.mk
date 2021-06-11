LOCAL_PATH := $(call my-dir)

boots_socket_path := "\"/data/misc/\""

#- boots -------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_CFLAGS := -Werror -Wall
LOCAL_SRC_FILES := \
    boots.c \
    boots_pkt.c \
    boots_skt.c \
    boots_eth.c \
    boots_uart.c \
    boots_script.c

LOCAL_CFLAGS += -DBOOTS_SOCKET_PATH=$(boots_socket_path)
LOCAL_CFLAGS += -DANDROID_PLATFORM
LOCAL_C_INCLUDES := system/core/libcutils/include
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := boots
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_EXECUTABLE)

#- boots_srv ----------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_CFLAGS := -Werror -Wall
LOCAL_SRC_FILES := \
    boots_srv.c \
    boots_btif.c \
    boots_pkt.c \
    boots_skt.c \
    boots_eth.c \
    boots_mt6xx.c \
    boots_uart.c \
    boots_script.c

LOCAL_CFLAGS += -DBOOTS_SOCKET_PATH=$(boots_socket_path)
LOCAL_CFLAGS += -DANDROID_PLATFORM
LOCAL_C_INCLUDES := system/core/libcutils/include
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := boots_srv
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_EXECUTABLE)
