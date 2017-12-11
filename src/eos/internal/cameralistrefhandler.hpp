#pragma once

#include <edsdk/EDSDKTypes.h>

namespace EOS {
  namespace Internal {
    class CameraListRefHandler {
    public:
      CameraListRefHandler();
      ~CameraListRefHandler();
      EdsCameraListRef getCameraListRef();
      bool isInitialized();

    private:
      EdsCameraListRef mCameraListRef;
      bool mInitialized;
    };
  }
}
