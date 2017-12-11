#pragma once

#include <memory>

namespace EOS {
  class Camera;

  class CameraConnectionStatusListener {
  public:
    virtual ~CameraConnectionStatusListener() = default;
    virtual void cameraConnected(const std::shared_ptr<Camera> &camera) = 0;
    virtual void cameraDisconnected(const std::shared_ptr<Camera> &camera) = 0;
  };
}
