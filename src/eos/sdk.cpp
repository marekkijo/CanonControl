#include "sdk.hpp"

#include "internal/sdkimpl.hpp"

namespace EOS {
  SDK::SDK()
    : pImpl{std::make_unique<Internal::SDKImpl>()} {
  }

  SDK::~SDK() {
  }

  void SDK::registerDeviceListChangedListener(std::weak_ptr<DeviceListChangedListener> deviceListChangedListener) {
    pImpl->registerDeviceListChangedListener(deviceListChangedListener);
  }

  void SDK::registerDeviceConnectionStatusListener(std::weak_ptr<DeviceConnectionStatusListener> deviceConnectionStatusListener) {
    pImpl->registerDeviceConnectionStatusListener(deviceConnectionStatusListener);
  }

  void SDK::refreshNotify() {
    pImpl->refreshNotify();
  }
}
