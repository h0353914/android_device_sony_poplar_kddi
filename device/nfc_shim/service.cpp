#include <android-base/logging.h>
#include <android/hardware/nfc/1.2/INfc.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>

#include "NfcShim.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::hardware::nfc::V1_2::INfc;
using android::hardware::nfc::V1_2::implementation::NfcShim;
using android::sp;

int main() {
    sp<INfc> nfc = new NfcShim();
    configureRpcThreadpool(1, true);
    android::status_t status = nfc->registerAsService("default");
    if (status != android::OK) {
        LOG(ERROR) << "Cannot register NFC HAL service";
        return 1;
    }
    LOG(INFO) << "NFC HAL Ready.";
    joinRpcThreadpool();
    LOG(ERROR) << "NFC HAL failed to join thread pool.";
    return 1;
}