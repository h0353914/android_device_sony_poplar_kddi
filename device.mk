### PLATFORM
$(call inherit-product, device/sony/yoshino-common/platform.mk)
### PROPRIETARY VENDOR FILES
$(call inherit-product, vendor/sony/poplar_kddi/poplar_kddi-vendor.mk)

ifeq ($(WITH_FDROID),true)
$(call inherit-product, vendor/fdroid/fdroid-vendor.mk)
endif

DEVICE_PATH := device/sony/poplar_kddi

# Soong
PRODUCT_SOONG_NAMESPACES += \
    $(DEVICE_PATH)

# Device uses high-density artwork where available
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREBUILT_DPI := xxhdpi xhdpi hdpi
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

DEVICE_PACKAGE_OVERLAYS += \
    $(DEVICE_PATH)/overlay

# NFC HAL init rc files to fix HIDL registration
PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/init/android.hardware.nfc@1.1-service.cxd22xx.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/android.hardware.nfc@1.1-service.cxd22xx.rc \
    $(DEVICE_PATH)/init/android.hardware.nfc@1.2-service.cxd22xx_shim.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/android.hardware.nfc@1.2-service.cxd22xx_shim.rc

# NFC VINTF manifest fragment
PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/vendor/etc/vintf/manifest/android.hardware.nfc.cxd22xx.xml:$(TARGET_COPY_OUT_VENDOR)/etc/vintf/manifest/android.hardware.nfc.cxd22xx.xml

# Ueventd rules (optional backup)
PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/ueventd.poplar_kddi.rc:$(TARGET_COPY_OUT_VENDOR)/ueventd.rc

include $(DEVICE_PATH)/device/*.mk
