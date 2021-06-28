# $(warning "clean widevine libraries")
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/system/vendor/lib/libdrmmtkwhitelist.so $(PRODUCT_OUT)/system/vendor/lib/liboemcrypto.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/system/vendor/lib/libwvm.so $(PRODUCT_OUT)/system/vendor/lib/drm/libdrmwvmplugin.so)
# ************************************************
# NEWER CLEAN STEPS MUST BE AT THE END OF THE LIST
# ************************************************
