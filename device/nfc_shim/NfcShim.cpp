#include "NfcShim.h"

#include <android-base/logging.h>
#include <android/hardware/nfc/1.0/types.h>
#include <android/hardware/nfc/1.1/INfc.h>
#include <android/hardware/nfc/1.2/INfc.h>
#include <hidl/Status.h>

using ::android::sp;
using ::android::hardware::Return;
using ::android::hardware::Void;

namespace android {
namespace hardware {
namespace nfc {
namespace V1_2 {
namespace implementation {

NfcShim::NfcShim() {
    // Try named instance first, then fallback to default
    mNfc11 = V1_1::INfc::getService("cxd22xx");
    if (mNfc11 == nullptr) {
        mNfc11 = V1_1::INfc::getService();
    }
    if (mNfc11 == nullptr) {
        LOG(ERROR) << "NfcShim: failed to get underlying 1.1 INfc";
    } else {
        LOG(INFO) << "NfcShim: underlying 1.1 INfc acquired";
    }
}

// V1_0::INfc
Return<V1_0::NfcStatus> NfcShim::open(const sp<V1_0::INfcClientCallback>& clientCallback) {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->open(clientCallback);
}

// V1_2: return number of bytes written; bridge from 1.1 NfcStatus
Return<uint32_t> NfcShim::write(const ::android::hardware::hidl_vec<uint8_t>& data) {
    if (!mNfc11) return static_cast<uint32_t>(0);

    auto ret = mNfc11->write(data); // V1.1 returns NfcStatus
    if (!ret.isOk()) {
        LOG(ERROR) << "NfcShim::write: transport error";
        return static_cast<uint32_t>(0);
    }
    V1_0::NfcStatus st = ret; // unwrap
    if (st == V1_0::NfcStatus::OK) {
        return static_cast<uint32_t>(data.size());
    }
    return static_cast<uint32_t>(0);
}

Return<V1_0::NfcStatus> NfcShim::coreInitialized(const ::android::hardware::hidl_vec<uint8_t>& data) {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->coreInitialized(data);
}

Return<V1_0::NfcStatus> NfcShim::prediscover() {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->prediscover();
}

Return<V1_0::NfcStatus> NfcShim::close() {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->close();
}

Return<V1_0::NfcStatus> NfcShim::controlGranted() {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->controlGranted();
}

Return<V1_0::NfcStatus> NfcShim::powerCycle() {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->powerCycle();
}

// V1_1::INfc
Return<V1_0::NfcStatus> NfcShim::open_1_1(const sp<V1_1::INfcClientCallback>& clientCallback) {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->open_1_1(clientCallback);
}

Return<Void> NfcShim::factoryReset() {
    if (mNfc11) mNfc11->factoryReset();
    return Void();
}

Return<V1_0::NfcStatus> NfcShim::closeForPowerOffCase() {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->closeForPowerOffCase();
}

// V1_2::INfc
Return<Void> NfcShim::getConfig(getConfig_cb _hidl_cb) {
    V1_2::NfcConfig cfg = {};
    _hidl_cb(cfg);
    return Void();
}

}  // namespace implementation
}  // namespace V1_2
}  // namespace nfc
}  // namespace hardware
}  // namespace android