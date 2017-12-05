#include "controllerimpl.hpp"

#include "../exceptions.hpp"
#include "sdkrefhandler.hpp"

namespace EOS {
  namespace Internal {
    ControllerImpl::ControllerImpl()
    : mSDKRefHandler(std::make_unique<SDKRefHandler>()) {
        if (!mSDKRefHandler->isInitialized()) {
          throw InitializationException();
        }
    }

    ControllerImpl::~ControllerImpl() {
    }/*

    ControllerImpl::~ControllerImpl() {
      if (isInitialized()) {
        verifyCall(EdsTerminateSDK());
        mSdkInitialized = false;
      }
    }

    bool ControllerImpl::isInitialized() {
      return mSdkInitialized;
    }

    bool ControllerImpl::startCameraListChangeListener() {
      if (!verifyCall(EdsSetCameraAddedHandler(CameraController::CameraAddedHandlerCallback, this))) {
        return false;
      }
      mCameraListTimer.setInterval(3000);
      connect(&mCameraListTimer, SIGNAL(timeout()), this, SLOT(updateCameraList()));
      mCameraListTimer.start();
      return true;
    }

    std::string ControllerImpl::getErrorDescription() {
      return errorToString(getLastError());
    }

    EdsError ControllerImpl::CameraAddedHandler() {
      updateCameraList();
      return EDS_ERR_OK;
    }

    EdsError ControllerImpl::CameraAddedHandlerCallback(EdsVoid *inContext) {
      CameraController *cc = static_cast<CameraController *>(inContext);
      return cc->CameraAddedHandler();
    }

    void ControllerImpl::updateCameraList() {
      auto newCameraList = std::make_shared<CameraList>();
      if (!mCameraList || (mCameraList->getCamerasInfo() != newCameraList->getCamerasInfo())) {
        mCameraList = newCameraList;
        emit camerasListChanged(mCameraList->getCamerasInfo());
      }
    }*/
  }
}
