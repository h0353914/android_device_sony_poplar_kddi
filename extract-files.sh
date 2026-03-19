#!/bin/bash
#
# SPDX-FileCopyrightText: 2016 The CyanogenMod Project
# SPDX-FileCopyrightText: 2017-2025 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

function blob_fixup() {
    case "${1}" in
        vendor/lib/hw/audio.primary.msm8998.so)
            # Fix referenced set_sched_policy for stock audio hal
            [ "$2" = "" ] && return 0
            "${PATCHELF}" --replace-needed "libcutils.so" "libprocessgroup.so" "$2"
            ;;
        vendor/bin/qns)
            # Replace libstdc++.so with libstdc++_vendor.so
            [ "$2" = "" ] && return 0
            "${PATCHELF_0_17_2}" --replace-needed "libstdc++.so" "libstdc++_vendor.so" "$2"
            ;;
        vendor/lib/com.qualcomm.qti.ant@1.0.so | \
            vendor/lib/vendor.qti.voiceprint@1.0.so | \
            vendor/lib/vendor.semc.hardware.light@1.0.so | \
            vendor/lib/vendor.semc.system.idd@1.0.so | \
            vendor/lib/vendor.somc.hardware.camera.cacao@1.0.so | \
            vendor/lib/vendor.somc.hardware.camera.cacao@2.0.so | \
            vendor/lib/vendor.somc.hardware.camera.cacao@3.0.so | \
            vendor/lib/vendor.somc.hardware.camera.cacao@3.1.so | \
            vendor/lib/vendor.somc.hardware.camera.device@1.0.so | \
            vendor/lib/vendor.somc.hardware.camera.provider@1.0.so | \
            vendor/lib64/com.fingerprints.extension@1.0.so | \
            vendor/lib64/com.qualcomm.qti.ant@1.0.so | \
            vendor/lib64/vendor.display.color@1.0.so | \
            vendor/lib64/vendor.display.color@1.1.so | \
            vendor/lib64/vendor.display.postproc@1.0.so | \
            vendor/lib64/vendor.qti.esepowermanager@1.0.so | \
            vendor/lib64/vendor.qti.hardware.qdutils_disp@1.0.so | \
            vendor/lib64/vendor.qti.hardware.qteeconnector@1.0.so | \
            vendor/lib64/vendor.qti.hardware.tui_comm@1.0.so | \
            vendor/lib64/vendor.semc.hardware.light@1.0.so | \
            vendor/lib64/vendor.semc.hardware.thermal@1.0.so | \
            vendor/lib64/vendor.semc.system.idd@1.0.so | \
            vendor/lib64/vendor.somc.hardware.security.secd@1.0.so)
            # Use libhidlbase-v32 for select Android P blobs
            [ "$2" = "" ] && return 0
            "${PATCHELF}" --replace-needed "libhidlbase.so" "libhidlbase-v32.so" "$2"
            ;;
        *)
            return 1
            ;;
    esac

    return 0
}

function blob_fixup_dry() {
    blob_fixup "$1" ""
}

# If we're being sourced by the common script that we called,
# stop right here. No need to go down the rabbit hole.
if [ "${BASH_SOURCE[0]}" != "${0}" ]; then
    return
fi

set -e

export DEVICE=poplar_kddi
export DEVICE_COMMON=yoshino-common
export VENDOR=sony
export VENDOR_COMMON=${VENDOR}

"./../../${VENDOR_COMMON}/${DEVICE_COMMON}/extract-files.sh" "$@"
