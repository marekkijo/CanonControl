#include "sdkimpl.hpp"

#include "sdkrefhandler.hpp"
#include "../exceptions.hpp"
#include "../deviceconnectionstatuslistener.hpp"
#include "../devicelistchangedlistener.hpp"

namespace EOS {
  namespace Internal {
    SDKImpl::SDKImpl()
    : mSDKRefHandler(std::make_unique<SDKRefHandler>()) {
        if (!mSDKRefHandler->isInitialized()) {
          throw InitializationException();
        }
    }

    SDKImpl::~SDKImpl() {
    }/*

    SDKImpl::~SDKImpl() {
      if (isInitialized()) {
        verifyCall(EdsTerminateSDK());
        mSdkInitialized = false;
      }
    }

    bool SDKImpl::isInitialized() {
      return mSdkInitialized;
    }

    bool SDKImpl::startCameraListChangeListener() {
      if (!verifyCall(EdsSetCameraAddedHandler(CameraController::CameraAddedHandlerCallback, this))) {
        return false;
      }
      mCameraListTimer.setInterval(3000);
      connect(&mCameraListTimer, SIGNAL(timeout()), this, SLOT(updateCameraList()));
      mCameraListTimer.start();
      return true;
    }

    std::string SDKImpl::getErrorDescription() {
      return errorToString(getLastError());
    }

    EdsError SDKImpl::CameraAddedHandler() {
      updateCameraList();
      return EDS_ERR_OK;
    }

    EdsError SDKImpl::CameraAddedHandlerCallback(EdsVoid *inContext) {
      CameraController *cc = static_cast<CameraController *>(inContext);
      return cc->CameraAddedHandler();
    }

    void SDKImpl::updateCameraList() {
      auto newCameraList = std::make_shared<CameraList>();
      if (!mCameraList || (mCameraList->getCamerasInfo() != newCameraList->getCamerasInfo())) {
        mCameraList = newCameraList;
        emit camerasListChanged(mCameraList->getCamerasInfo());
      }
    }*/
    void SDKImpl::registerDeviceListChangedListener(std::weak_ptr<DeviceListChangedListener> deviceListChangedListener) {
    }

    void SDKImpl::registerDeviceConnectionStatusListener(std::weak_ptr<DeviceConnectionStatusListener> deviceConnectionStatusListener) {
    }

    void SDKImpl::refreshNotify() {
    }
  }
}
