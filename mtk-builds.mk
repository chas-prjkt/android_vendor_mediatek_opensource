#
# Copyright (C) 2020 The PixelExperience Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Call Custom (MTK)
$(call inherit-product, vendor/mediatek/opensource/custom/mtk-custom.mk)

# Call External (MTK)
$(call inherit-product, vendor/mediatek/opensource/external/mtk-external.mk)

# Call Frameworks (MTK)
$(call inherit-product, vendor/mediatek/opensource/frameworks/mtk-frameworks.mk)

# Call Hardware (MTK)
$(call inherit-product, vendor/mediatek/opensource/hardware/mtk-hardware.mk)

# Call System (MTK)
$(call inherit-product, vendor/mediatek/opensource/system/mtk-system.mk)

# Call Trustzone (MTK)
$(call inherit-product, vendor/mediatek/opensource/trustzone/mtk-trustzone.mk)

# Call Interfaces (MTK)
$(call inherit-product, vendor/mediatek/opensource/mtk-interfaces.mk)
