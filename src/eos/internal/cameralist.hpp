#pragma once

#include <memory>
#include <vector>

namespace EOS {
  class CameraInfo;

  namespace Internal {
    class CameraListRefHandler;

    class CameraList {
    public:
      CameraList();
      ~CameraList();
      const std::vector<CameraInfo> &getCamerasInfo();

    private:
      std::shared_ptr<CameraListRefHandler> mCameraListRefHandler;
      std::vector<CameraInfo> mCamerasInfo;

      void init();
    };
  }
}
