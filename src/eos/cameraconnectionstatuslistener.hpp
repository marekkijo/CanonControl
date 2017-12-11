#pragma once

#include <memory>

namespace EOS {
  class Camera;

  class CameraConnectionStatusListener {
  public:
    virtual ~CameraConnectionStatusListener() = default;
    virtual void cameraConnected(std::shared_ptr<Camera> &camera) = 0;
    virtual void cameraDisconnected(std::shared_ptr<Camera> &camera) = 0;
  };
}
