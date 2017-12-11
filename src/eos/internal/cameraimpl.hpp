#pragma once

#include <memory>

#include "../camera.hpp"

namespace EOS {
  namespace Internal {
    class CameraListRefHandler;
    class CameraRefHandler;

    class CameraImpl : public Camera {
    public:
      CameraImpl(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index);
      ~CameraImpl() override;

    private:
      std::unique_ptr<CameraRefHandler> mCameraRefHandler;
    };
  }
}
