#pragma once

#include <cstdint>

namespace EOS {
  class CameraParameterChangedListener {
  public:
    virtual ~CameraParameterChangedListener() = default;
    virtual void cameraPropertyUpdate_isoSpeed(std::uint32_t value) = 0;
  };
}
