#define LOG_TAG "android.hardware.nfc@1.2-service.cxd22xx_shim"

#include <android/hardware/nfc/1.2/INfc.h>
#include <hidl/HidlTransportSupport.h>
#include <hidl/LegacySupport.h>
#include <log/log.h>

#include "NfcShim.h"

using android::hardware::nfc::V1_2::INfc;
using android::hardware::nfc::V1_2::implementation::NfcShim;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

int main() {
    ALOGD("NFC HAL 1.2 Shim Service starting");

    android::sp<INfc> nfc = new NfcShim();

    configureRpcThreadpool(1, true);
    android::status_t status = nfc->registerAsService();

    if (status != android::OK) {
        ALOGE("Cannot register NFC HAL 1.2 service: %d", status);
        return 1;
    }

    ALOGD("NFC HAL 1.2 Shim Service ready");
    joinRpcThreadpool();

    ALOGD("NFC HAL 1.2 Shim Service shutting down");
    return 1; // should never get here
}