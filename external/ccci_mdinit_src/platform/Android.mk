LOCAL_SHARED_LIBRARIES += libcutils liblog libc libnvram libccci_util libhardware_legacy libdl

LOCAL_C_INCLUDES += vendor/mediatek/opensource/external/nvram/libnvram
LOCAL_SRC_FILES += platform/mdinit_platform.c platform/mdinit_relate.c platform/md_init.c
