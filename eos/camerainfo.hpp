#pragma once

#include <string>
#include <cstdint>

#include <edsdk/EDSDK.h>
#include <edsdk/EDSDKTypes.h>
#include <edsdk/EDSDKErrors.h>

namespace EOS {
  struct CameraInfo {
    EdsUInt32 index;
    std::string portName;
    std::string description;
    std::uint32_t subType;
    std::uint32_t reserved;
  };

  bool operator==(const CameraInfo& lhs, const CameraInfo& rhs);
}
