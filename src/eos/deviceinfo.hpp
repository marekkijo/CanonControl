#pragma once

#include <cstdint>
#include <string>

namespace EOS {
  struct DeviceInfo {
    std::size_t index;
    std::string portName;
    std::string description;
    std::uint32_t subtype;
    std::uint32_t reserved;
  };

  bool operator==(const DeviceInfo& lhs, const DeviceInfo& rhs);
}
