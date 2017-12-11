#pragma once

#include <memory>
#include <cstddef>

#include <edsdk/EDSDKTypes.h>

namespace EOS {
  namespace Internal {
    class CameraListRefHandler;

    class CameraRefHandler {
    public:
      CameraRefHandler(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index);
      ~CameraRefHandler();
      EdsCameraRef getCameraRef();
      bool isInitialized();

    private:
      std::shared_ptr<CameraListRefHandler> mCameraListRefHandler;
      EdsCameraRef mCameraRef;
      bool mInitialized;
    };
  }
}
