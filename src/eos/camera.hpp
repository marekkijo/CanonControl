#pragma once

namespace EOS {
  class CameraInfo;

  class Camera {
  public:
    virtual ~Camera() = default;
    virtual const CameraInfo &getCameraInfo() const = 0;
    virtual void setCameraProperty_isoSpeed(std::uint32_t value) = 0;
  };
}
