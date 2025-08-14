#define LOG_TAG "android.hardware.nfc@1.2-service.cxd22xx_shim"

#include "NfcShim.h"

#include <android/hardware/nfc/1.0/types.h>
#include <android/hardware/nfc/1.1/INfc.h>
#include <android/hardware/nfc/1.2/types.h>
#include <log/log.h>

namespace android {
namespace hardware {
namespace nfc {
namespace V1_2 {
namespace implementation {

NfcShim::NfcShim() {
    ALOGD("NfcShim constructor");
    mNfcV11 = V1_1::INfc::getService();
    if (mNfcV11 == nullptr) {
        ALOGE("Failed to get V1_1::INfc service");
    } else {
        ALOGD("Successfully obtained V1_1::INfc service");
    }
}

// Methods from V1_0::INfc
Return<V1_0::NfcStatus> NfcShim::open(const sp<V1_0::INfcClientCallback>& clientCallback) {
    ALOGD("NfcShim::open");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->open(clientCallback);
}

Return<uint32_t> NfcShim::write(const hidl_vec<uint8_t>& data) {
    ALOGV("NfcShim::write");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return 0;
    }
    return mNfcV11->write(data);
}

Return<V1_0::NfcStatus> NfcShim::coreInitialized(const hidl_vec<uint8_t>& data) {
    ALOGD("NfcShim::coreInitialized");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->coreInitialized(data);
}

Return<V1_0::NfcStatus> NfcShim::prediscover() {
    ALOGD("NfcShim::prediscover");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->prediscover();
}

Return<V1_0::NfcStatus> NfcShim::close() {
    ALOGD("NfcShim::close");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->close();
}

Return<V1_0::NfcStatus> NfcShim::controlGranted() {
    ALOGD("NfcShim::controlGranted");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->controlGranted();
}

Return<V1_0::NfcStatus> NfcShim::powerCycle() {
    ALOGD("NfcShim::powerCycle");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->powerCycle();
}

// Methods from V1_1::INfc
Return<void> NfcShim::factoryReset() {
    ALOGD("NfcShim::factoryReset");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return Void();
    }
    return mNfcV11->factoryReset();
}

Return<V1_0::NfcStatus> NfcShim::closeForPowerOffCase() {
    ALOGD("NfcShim::closeForPowerOffCase");
    if (mNfcV11 == nullptr) {
        ALOGE("V1_1::INfc service is null");
        return V1_0::NfcStatus::FAILED;
    }
    return mNfcV11->closeForPowerOffCase();
}

// Methods from V1_2::INfc
Return<void> NfcShim::getConfig(getConfig_cb _hidl_cb) {
    ALOGD("NfcShim::getConfig");
    // V1_2 specific method - return minimal config since V1_1 doesn't support this
    V1_2::NfcConfig config = {};
    
    // Initialize the config with safe defaults
    config.v1_1.v1_0.maxIsoDepTransceiveLength = 0xFEFF;  // Default max length
    config.v1_1.v1_0.maxNfceeBuffer = 0x400;  // 1KB buffer
    config.v1_1.v1_0.discoveryApi = V1_0::DiscoveryMethod::NFA_TECHNOLOGY_MASK;
    config.v1_1.v1_0.powderOffSuspend = 0x1;
    config.v1_1.v1_0.routingPowerState = 0x1;
    config.v1_1.defaultIsoDepRoute = 0x0;
    
    _hidl_cb(V1_0::NfcStatus::OK, config);
    return Void();
}

}  // namespace implementation
}  // namespace V1_2
}  // namespace nfc
}  // namespace hardware
}  // namespace android