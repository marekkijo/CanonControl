#include "cameraimpl.hpp"

#include <edsdk/EDSDK.h>

#include "camerarefhandler.hpp"
#include "utilities.hpp"
#include "../exceptions.hpp"
#include "../cameraparameterchangedlistener.hpp"

namespace EOS {
  namespace Internal {
    CameraImpl::CameraImpl(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index, CameraParameterChangedListener *cameraParameterChangedListener, const CameraInfo &cameraInfo)
      : mCameraRefHandler{std::make_unique<CameraRefHandler>(cameraListRefHandler, index)}
      , mCameraParameterChangedListener{cameraParameterChangedListener}
      , mCameraInfo{cameraInfo}
      , mInitialized{false} {
      if (!mCameraRefHandler->isInitialized() || !mCameraParameterChangedListener) {
        throw InitializationException();
      }

      if (!verifyCall(EdsSetPropertyEventHandler(mCameraRefHandler->getCameraRef(), kEdsPropertyEvent_All, handlePropertyEvent, this))) {
        return;
      }

      if (!verifyCall(EdsSetObjectEventHandler(mCameraRefHandler->getCameraRef(), kEdsObjectEvent_All, handleObjectEvent, this))) {
        return;
      }

      if (!verifyCall(EdsSetCameraStateEventHandler(mCameraRefHandler->getCameraRef(), kEdsStateEvent_All, handleCameraStateEvent, this))) {
        return;
      }

      mInitialized = verifyCall(EdsOpenSession(mCameraRefHandler->getCameraRef()));
    }

    CameraImpl::~CameraImpl() {
      if (mInitialized) {
        verifyCall(EdsCloseSession(mCameraRefHandler->getCameraRef()));
        mInitialized = false;
      }
    }

    bool CameraImpl::isInitialized() const {
      return mInitialized;
    }

    EdsCameraRef CameraImpl::getCameraRef() const {
      return mCameraRefHandler->getCameraRef();
    }

    const CameraInfo &CameraImpl::getCameraInfo() const {
      return mCameraInfo;
    }

    void CameraImpl::setCameraProperty_isoSpeed(std::uint32_t value) {
      verifyCall(EdsSetPropertyData(mCameraRefHandler->getCameraRef(), kEdsPropID_ISOSpeed, 0, sizeof(std::uint32_t), &value));
    }

    std::uint32_t CameraImpl::extractUInt32Value(EdsPropertyID inPropertyID, EdsInt32 inParam) const {
      EdsDataType outDataType;
      EdsUInt32 outSize;
      std::uint32_t outPropertyData;
      if (!verifyCall(EdsGetPropertySize(mCameraRefHandler->getCameraRef(), inPropertyID, inParam, &outDataType, &outSize)) ||
          (outDataType != kEdsDataType_UInt32) ||
          (outSize != sizeof(std::uint32_t)) ||
          !verifyCall(EdsGetPropertyData(mCameraRefHandler->getCameraRef(), inPropertyID, inParam, outSize, &outPropertyData))) {
        return 0;
      }

      return  outPropertyData;
    }

    void CameraImpl::handlePropertyEvent(EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam) {
      switch (inPropertyID) {
      case kEdsPropID_ISOSpeed: {
        static std::uint32_t lastValue = 0x0000FFFF;
        std::uint32_t currentValue = extractUInt32Value(inPropertyID, inParam);
        if (currentValue != lastValue) {
          lastValue = currentValue;
          mCameraParameterChangedListener->cameraPropertyUpdate_isoSpeed(currentValue);
        }
        break;
      }
      default:
        break;
      }
    }

    void CameraImpl::handleObjectEvent(EdsObjectEvent inEvent, EdsBaseRef inRef) {
    }

    void CameraImpl::handleCameraStateEvent(EdsStateEvent inEvent, EdsUInt32 inEventData) {
    }

    EdsError CameraImpl::handlePropertyEvent(EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam, EdsVoid *inContext) {
      CameraImpl *impl = static_cast<CameraImpl *>(inContext);
      impl->handlePropertyEvent(inEvent, inPropertyID, inParam);
      return EDS_ERR_OK;
    }

    EdsError CameraImpl::handleObjectEvent(EdsObjectEvent inEvent,  EdsBaseRef inRef, EdsVoid *inContext) {
      CameraImpl *impl = static_cast<CameraImpl *>(inContext);
      impl->handleObjectEvent(inEvent, inRef);
      return EDS_ERR_OK;
    }

    EdsError CameraImpl::handleCameraStateEvent(EdsStateEvent inEvent, EdsUInt32 inEventData, EdsVoid *inContext) {
      CameraImpl *impl = static_cast<CameraImpl *>(inContext);
      impl->handleCameraStateEvent(inEvent, inEventData);
      return EDS_ERR_OK;
    }
  }
}
