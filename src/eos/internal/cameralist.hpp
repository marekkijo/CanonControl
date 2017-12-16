#pragma once

#include <memory>
#include <vector>
#include <cstddef>

namespace EOS {
  class CameraInfo;
  class Camera;
  class CameraParameterChangedListener;

  namespace Internal {
    class CameraListRefHandler;

    class CameraList {
    public:
      CameraList();
      ~CameraList();
      const std::vector<CameraInfo> &getCamerasInfo() const;
      const std::shared_ptr<Camera> &getConnectedCamera() const;
      const std::shared_ptr<Camera> &connectCamera(std::size_t index, CameraParameterChangedListener *cameraParameterChangedListener);
      void disconnectCamera(const std::shared_ptr<Camera> &connectedCamera);
      bool reassignConnectedCamera(const std::shared_ptr<CameraList> &cameraList);

    private:
      std::shared_ptr<CameraListRefHandler> mCameraListRefHandler;
      std::vector<CameraInfo> mCamerasInfo;
      std::shared_ptr<Camera> mConnectedCamera;

      void init();
    };
  }
}
