#pragma once

#include <memory>

namespace EOS {
  class Device;

  class DeviceConnectionStatusListener {
  public:
    virtual ~DeviceConnectionStatusListener() = default;
    virtual void deviceConnected(std::shared_ptr<Device> &device) = 0;
    virtual void deviceDisconnected(std::shared_ptr<Device> &device) = 0;
  };
}
