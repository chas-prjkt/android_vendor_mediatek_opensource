#
# Copyright (C) 2020 The PixelExperience Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Connectivity
$(call inherit-product, vendor/mediatek/opensource/hardware/connectivity/connectivity_package.mk)

# Hardware
PRODUCT_PACKAGES += \
    fstb.cfg \
    libpowerhal \
    libkmsetkey \
    kmsetkey_ca \
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
    vendor.mediatek.hardware.mtkpower@1.0-service \
    vendor.mediatek.hardware.keymaster_attestation@1.1-impl \
    vendor.mediatek.hardware.keymaster_attestation@1.1-service
