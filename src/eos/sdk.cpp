#include "sdk.hpp"

#include "internal/sdkimpl.hpp"

namespace EOS {
  SDK::SDK()
    : pImpl{std::make_unique<Internal::SDKImpl>()} {
  }

  SDK::~SDK() {
  }

  void SDK::registerCameraListChangedListener(CameraListChangedListener *cameraListChangedListener) {
    pImpl->registerCameraListChangedListener(cameraListChangedListener);
  }

  void SDK::unregisterCameraListChangedListener(CameraListChangedListener *cameraListChangedListener) {
    pImpl->registerCameraListChangedListener(cameraListChangedListener);
  }

  void SDK::registerCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener) {
    pImpl->registerCameraConnectionStatusListener(cameraConnectionStatusListener);
  }

  void SDK::unregisterCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener) {
    pImpl->registerCameraConnectionStatusListener(cameraConnectionStatusListener);
  }

  void SDK::refreshNotify() {
    pImpl->refreshNotify();
  }

  void SDK::setCameraAddedHandler() {
    pImpl->setCameraAddedHandler();
  }

  void SDK::clearCameraAddedHandler() {
    pImpl->clearCameraAddedHandler();
  }

  void SDK::connectCamera(size_t index) {
    pImpl->connectCamera(index);
  }
}
