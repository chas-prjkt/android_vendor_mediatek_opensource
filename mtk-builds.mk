#
# Copyright (C) 2020 The PixelExperience Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Call Connectivity
$(call inherit-product, vendor/mediatek/opensource/hardware/connectivity/connectivity_package.mk)

# Call Interfaces (vendor)
$(call inherit-product, vendor/mediatek/opensource/mtk-interfaces.mk)

# External
PRODUCT_PACKAGES += \
    libudf \
    libhwm \
    ccci_fsd \
    libnvram \
    libladder \
    libfile_op \
    libperfctl \
    fuelgauged \
    ccci_mdinit \
    nvram_daemon \
    libnvram_sec \
    libcustom_nvram \
    fuelgauged_nvram \
    libperfctl_vendor \
    libmtkaudio_utils \
    libnvram_daemon_callback \
    vendor.mediatek.hardware.nvram@1.1-impl \
    vendor.mediatek.hardware.nvram@1.1-service

# hardware
PRODUCT_PACKAGES += \
    fstb.cfg \
    libpowerhal \
    libccci_util \
    libfpspolicy \
    power.default \
    powerscntbl.xml \
    libmtkperf_client \
    powercontable.xml \
    power_app_cfg.xml \
    libmtkaudio_utils \
    libfpspolicy-client \
    libpowerhalwrap_vendor \
    power_legacy_test_v_1_0 \
    power_native_test_v_1_0 \
    libmtkperf_client_vendor \
    libaudioprimarydevicehalifclient \
    vendor.mediatek.hardware.dfps@1.0-impl \
    vendor.mediatek.hardware.power@2.1-impl \
    android.hardware.audio.service.mediatek \
    android.hardware.audio@6.0-impl-mediatek \
    android.hardware.power@1.3-impl-mediatek \
    android.hardware.usb@1.1-service-mediatek \
    vendor.mediatek.hardware.dfps@1.0-service \
    vendor.mediatek.hardware.mtkpower@1.0-impl \
    vendor.mediatek.hardware.mtkpower@1.0-service
