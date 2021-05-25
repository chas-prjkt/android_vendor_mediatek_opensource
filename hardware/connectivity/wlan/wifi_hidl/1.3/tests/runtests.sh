#!/usr/bin/env bash

if [ -z $ANDROID_BUILD_TOP ]; then
  echo "You need to source and lunch before you can use this script"
  exit 1
fi
set -e

$ANDROID_BUILD_TOP/build/soong/soong_ui.bash --make-mode android.hardware.wifi@1.0-service-tests
adb root
adb sync data
adb shell /data/nativetest64/vendor/android.hardware.wifi@1.0-service-tests/android.hardware.wifi@1.0-service-tests
