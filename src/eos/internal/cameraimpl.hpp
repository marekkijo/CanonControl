#pragma once

#include <memory>

#include <edsdk/EDSDKTypes.h>

#include "../camera.hpp"
#include "../camerainfo.hpp"

namespace EOS {
  namespace Internal {
    class CameraListRefHandler;
    class CameraRefHandler;

    class CameraImpl : public Camera {
    public:
      CameraImpl(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index, const CameraInfo &cameraInfo);
      ~CameraImpl() override;
      bool isInitialized() const;
      EdsCameraRef getCameraRef() const;

    public: // Camera
      const CameraInfo &getCameraInfo() const override;

    private:
      std::unique_ptr<CameraRefHandler> mCameraRefHandler;
      CameraInfo mCameraInfo;
      bool mInitialized;
    };
  }
}
