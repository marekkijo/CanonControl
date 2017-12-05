#pragma once

#include <memory>

namespace EOS {
  namespace Internal {
    class SDKImpl;
  }
  class DeviceListChangedListener;
  class DeviceConnectionStatusListener;

  class SDK {
  public:
    SDK();
    ~SDK();
    void registerDeviceListChangedListener(std::weak_ptr<DeviceListChangedListener> deviceListChangedListener);
    void registerDeviceConnectionStatusListener(std::weak_ptr<DeviceConnectionStatusListener> deviceConnectionStatusListener);
    void refreshNotify();

  private:
    const std::unique_ptr<Internal::SDKImpl> pImpl;
  };
}
