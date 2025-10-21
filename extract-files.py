#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)
from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)

namespace_imports = [
    'hardware/qcom-caf/msm8998',
    'hardware/qcom-caf/wlan',
    'vendor/sony/yoshino-common',
]

blob_fixups: blob_fixups_user_type = {
    'vendor/lib/hw/audio.primary.msm8998.so': blob_fixup()
        .replace_needed('libcutils.so', 'libprocessgroup.so'),
    'vendor/bin/qns': blob_fixup()
        .replace_needed('libstdc++.so', 'libstdc++_vendor.so'),
    (
        'vendor/lib/com.qualcomm.qti.ant@1.0.so',
        'vendor/lib/vendor.qti.voiceprint@1.0.so',
        'vendor/lib/vendor.semc.hardware.light@1.0.so',
        'vendor/lib/vendor.semc.system.idd@1.0.so',
        'vendor/lib/vendor.somc.hardware.camera.cacao@1.0.so',
        'vendor/lib/vendor.somc.hardware.camera.cacao@2.0.so',
        'vendor/lib/vendor.somc.hardware.camera.cacao@3.0.so',
        'vendor/lib/vendor.somc.hardware.camera.cacao@3.1.so',
        'vendor/lib/vendor.somc.hardware.camera.device@1.0.so',
        'vendor/lib/vendor.somc.hardware.camera.provider@1.0.so',
        'vendor/lib64/com.fingerprints.extension@1.0.so',
        'vendor/lib64/com.qualcomm.qti.ant@1.0.so',
        'vendor/lib64/vendor.display.color@1.0.so',
        'vendor/lib64/vendor.display.color@1.1.so',
        'vendor/lib64/vendor.display.postproc@1.0.so',
        'vendor/lib64/vendor.qti.esepowermanager@1.0.so',
        'vendor/lib64/vendor.qti.hardware.qdutils_disp@1.0.so',
        'vendor/lib64/vendor.qti.hardware.qteeconnector@1.0.so',
        'vendor/lib64/vendor.qti.hardware.tui_comm@1.0.so',
        'vendor/lib64/vendor.semc.hardware.light@1.0.so',
        'vendor/lib64/vendor.semc.hardware.thermal@1.0.so',
        'vendor/lib64/vendor.semc.system.idd@1.0.so',
        'vendor/lib64/vendor.somc.hardware.security.secd@1.0.so',
    ): blob_fixup()
        .replace_needed('libhidlbase.so', 'libhidlbase-v32.so'),
}  # fmt: skip

module = ExtractUtilsModule(
    'poplar_kddi',
    'sony',
    blob_fixups=blob_fixups,
    check_elf=False,
    namespace_imports=namespace_imports,
)

if __name__ == '__main__':
    utils = ExtractUtils.device_with_common(
        module, 'yoshino-common', module.vendor
    )
    utils.run()
