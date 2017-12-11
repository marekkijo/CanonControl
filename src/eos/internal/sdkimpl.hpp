#pragma once

#include <memory>
#include <vector>
#include <unordered_set>

#include <edsdk/EDSDKTypes.h>

namespace EOS {
  class CameraInfo;
  class Camera;
  class CameraListChangedListener;
  class CameraConnectionStatusListener;

  namespace Internal {
    class SDKRefHandler;
    class CameraList;

    class SDKImpl {
    public:
      SDKImpl();
      ~SDKImpl();
      void registerCameraListChangedListener(CameraListChangedListener *cameraListChangedListener);
      void unregisterCameraListChangedListener(CameraListChangedListener *cameraListChangedListener);
      void registerCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener);
      void unregisterCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener);
      void refreshNotify();
      void setCameraAddedHandler();
      void clearCameraAddedHandler();
      void connectCamera(size_t index);
      void disconnectCamera(const std::shared_ptr<Camera> &camera);

    private:
      std::unique_ptr<SDKRefHandler> mSDKRefHandler;
      std::shared_ptr<CameraList> mCameraList;
      std::unordered_set<CameraListChangedListener *> mCameraListChangedListeners;
      std::unordered_set<CameraConnectionStatusListener *> mCameraConnectionStatusListeners;

      void notifyListenersCameraListChanged(const std::vector<CameraInfo> &cameraList);
      void notifyListenersCameraConnected(const std::shared_ptr<Camera> &camera);
      void notifyListenersCameraDisconnected(const std::shared_ptr<Camera> &camera);
      void cameraAddedHandler();

      static EdsError EDSCALLBACK cameraAddedHandler(EdsVoid *inContext);
    };
  }
}
