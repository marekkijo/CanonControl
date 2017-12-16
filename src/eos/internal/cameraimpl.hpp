#pragma once

#include <memory>

#include <edsdk/EDSDKTypes.h>

#include "../camera.hpp"
#include "../camerainfo.hpp"

namespace EOS {
  class CameraParameterChangedListener;

  namespace Internal {
    class CameraListRefHandler;
    class CameraRefHandler;

    class CameraImpl : public Camera {
    public:
      CameraImpl(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index, CameraParameterChangedListener *cameraParameterChangedListener, const CameraInfo &cameraInfo);
      ~CameraImpl() override;
      bool isInitialized() const;
      EdsCameraRef getCameraRef() const;

    public: // Camera
      const CameraInfo &getCameraInfo() const override;
      void setCameraProperty_isoSpeed(std::uint32_t value) override;

    private:
      std::unique_ptr<CameraRefHandler> mCameraRefHandler;
      CameraParameterChangedListener *mCameraParameterChangedListener;
      CameraInfo mCameraInfo;
      bool mInitialized;

      std::uint32_t extractUInt32Value(EdsPropertyID inPropertyID, EdsInt32 inParam) const;
      void handlePropertyEvent(EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam);
      void handleObjectEvent(EdsObjectEvent inEvent, EdsBaseRef inRef);
      void handleCameraStateEvent(EdsStateEvent inEvent, EdsUInt32 inEventData);

      static EdsError EDSCALLBACK handlePropertyEvent(EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam, EdsVoid *inContext);
      static EdsError EDSCALLBACK handleObjectEvent(EdsObjectEvent inEvent, EdsBaseRef inRef, EdsVoid *inContext);
      static EdsError EDSCALLBACK handleCameraStateEvent(EdsStateEvent inEvent, EdsUInt32 inEventData, EdsVoid *inContext);
    };
  }
}
