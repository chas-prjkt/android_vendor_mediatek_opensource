MTK_HARD_ROOT_PATH := $(call my-dir)

# MTK CCCI
include $(MTK_HARD_ROOT_PATH)/ccci/Android.mk

# MTK Connectivity
include $(MTK_HARD_ROOT_PATH)/connectivity/Android.mk

# MTK Consumerir
include $(MTK_HARD_ROOT_PATH)/consumerir/Android.mk

# MTK Libdfps
include $(MTK_HARD_ROOT_PATH)/libdfps/Android.mk

# MTK Libkmsetkey
include $(MTK_HARD_ROOT_PATH)/libkmsetkey/Android.mk

# MTK Power
include $(MTK_HARD_ROOT_PATH)/power/service/Power/1.3/Android.mk
include $(MTK_HARD_ROOT_PATH)/power/service/main/Android.mk
include $(MTK_HARD_ROOT_PATH)/power/service/MtkPower/1.0/Android.mk
include $(MTK_HARD_ROOT_PATH)/power/service/LegacyPower/2.1/Android.mk
include $(MTK_HARD_ROOT_PATH)/power/lib/powerhal/Android.mk
include $(MTK_HARD_ROOT_PATH)/power_util/mtkperf_client/Android.mk
include $(MTK_HARD_ROOT_PATH)/power_util/powerhalwrap_v_2_0/Android.mk
include $(MTK_HARD_ROOT_PATH)/power/module/Android.mk
include $(MTK_HARD_ROOT_PATH)/power/config/Android.mk

# MTK Thermal
include $(MTK_HARD_ROOT_PATH)/thermal/Android.mk
