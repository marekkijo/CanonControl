#pragma once

#include <cstdint>
#include <string>

namespace EOS {
  struct CameraInfo {
    std::size_t index;
    std::string portName;
    std::string description;
    std::uint32_t subtype;
    std::uint32_t reserved;
  };

  bool operator==(const CameraInfo& lhs, const CameraInfo& rhs);
}
