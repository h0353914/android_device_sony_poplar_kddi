#include "NfcShim.h"

#include <android-base/logging.h>
#include <android/hardware/nfc/1.0/types.h>
#include <android/hardware/nfc/1.1/INfc.h>
#include <android/hardware/nfc/1.1/types.h>
#include <android/hardware/nfc/1.2/INfc.h>
#include <android/hardware/nfc/1.2/types.h>
#include <hidl/Status.h>

using ::android::sp;
using ::android::hardware::Return;

namespace android {
namespace hardware {
namespace nfc {
namespace V1_2 {
namespace implementation {

NfcShim::NfcShim() {
    // 先嘗試命名實例，再回退到 default
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

// V1_2 write: 直接轉回底層 HAL 回傳的 bytes written
Return<uint32_t> NfcShim::write(const ::android::hardware::hidl_vec<uint8_t>& data) {
    if (!mNfc11) return static_cast<uint32_t>(0);

    auto ret = mNfc11->write(data); // V1.0/1.1: Return<uint32_t>
    if (!ret.isOk()) {
        LOG(ERROR) << "NfcShim::write: transport error";
        return static_cast<uint32_t>(0);
    }
    uint32_t bytes = ret; // unwrap
    return bytes;
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

Return<void> NfcShim::factoryReset() {
    if (mNfc11) mNfc11->factoryReset();
    return {};
}

Return<V1_0::NfcStatus> NfcShim::closeForPowerOffCase() {
    if (!mNfc11) return V1_0::NfcStatus::FAILED;
    return mNfc11->closeForPowerOffCase();
}

// V1_2::INfc
// 注意：1.2 保留舊的 getConfig(...)，其 callback 型別對應 1.1 的 NfcConfig
Return<void> NfcShim::getConfig(getConfig_cb _hidl_cb) {
    ::android::hardware::nfc::V1_1::NfcConfig cfg11 = {};
    _hidl_cb(cfg11);
    return {};
}

// 1.2 新增的 getConfig_1_2(...)，使用 1.2 版 NfcConfig
Return<void> NfcShim::getConfig_1_2(getConfig_1_2_cb _hidl_cb) {
    ::android::hardware::nfc::V1_2::NfcConfig cfg12 = {};
    _hidl_cb(cfg12);
    return {};
}

}  // namespace implementation
}  // namespace V1_2
}  // namespace nfc
}  // namespace hardware
}  // namespace android