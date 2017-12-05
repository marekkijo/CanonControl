#pragma once

#include <memory>

namespace EOS {
  class DeviceListChangedListener;
  class DeviceConnectionStatusListener;

  namespace Internal {
    class SDKRefHandler;

    class SDKImpl {
    public:
      SDKImpl();
      ~SDKImpl();
      void registerDeviceListChangedListener(std::weak_ptr<DeviceListChangedListener> deviceListChangedListener);
      void registerDeviceConnectionStatusListener(std::weak_ptr<DeviceConnectionStatusListener> deviceConnectionStatusListener);
      void refreshNotify();

    private:
      std::unique_ptr<SDKRefHandler> mSDKRefHandler;
    };
  }
}
