#pragma once

#include <vector>

namespace EOS {
  class DeviceInfo;

  class DeviceListChangedListener {
  public:
    virtual ~DeviceListChangedListener() = default;
    virtual void deviceListChanged(const std::vector<DeviceInfo> &deviceList) = 0;
  };
}
