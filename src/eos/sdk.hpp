#pragma once

#include <memory>

namespace EOS {
  namespace Internal {
    class SDKImpl;
  }
  class CameraListChangedListener;
  class CameraConnectionStatusListener;
  class CameraParameterChangedListener;
  class Camera;

  class SDK {
  public:
    SDK();
    ~SDK();
    void registerCameraListChangedListener(CameraListChangedListener *cameraListChangedListener);
    void unregisterCameraListChangedListener(CameraListChangedListener *cameraListChangedListener);
    void registerCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener);
    void unregisterCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener);
    void refreshNotify();
    void setCameraAddedHandler();
    void clearCameraAddedHandler();
    void connectCamera(size_t index, CameraParameterChangedListener *cameraParameterChangedListener);
    void disconnectCamera(const std::shared_ptr<EOS::Camera> &camera);

  private:
    const std::unique_ptr<Internal::SDKImpl> pImpl;
  };
}
