#pragma once

#include <android/hardware/nfc/1.2/INfc.h>
#include <android/hardware/nfc/1.1/INfc.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace nfc {
namespace V1_2 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::nfc::V1_0::NfcEvent;
using ::android::hardware::nfc::V1_0::NfcStatus;
using ::android::hardware::nfc::V1_1::INfc;
using ::android::sp;

struct NfcShim : public V1_2::INfc {
public:
    NfcShim();

    // Methods from V1_0::INfc follow.
    Return<NfcStatus> open(const sp<V1_0::INfcClientCallback>& clientCallback) override;
    Return<NfcStatus> write(const hidl_vec<uint8_t>& data) override;
    Return<NfcStatus> coreInitialized(const hidl_vec<uint8_t>& data) override;
    Return<NfcStatus> prediscover() override;
    Return<NfcStatus> close() override;
    Return<NfcStatus> controlGranted() override;
    Return<NfcStatus> powerCycle() override;

    // Methods from V1_1::INfc follow.
    Return<void> factoryReset() override;
    Return<NfcStatus> closeForPowerOffCase() override;

    // Methods from V1_2::INfc follow.
    Return<void> getConfig(getConfig_cb _hidl_cb) override;

private:
    sp<V1_1::INfc> mNfc11;
};

}  // namespace implementation
}  // namespace V1_2
}  // namespace nfc
}  // namespace hardware
}  // namespace android