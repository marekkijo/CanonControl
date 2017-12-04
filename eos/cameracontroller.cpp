#include "cameracontroller.hpp"

#include "utilities.hpp"

namespace EOS {
  CameraController::CameraController(QObject *parent)
    : QObject(parent)
    , mSdkInitialized{verifyCall(EdsInitializeSDK())} {
  }

  CameraController::~CameraController() {
    if (isInitialized()) {
      verifyCall(EdsTerminateSDK());
      mSdkInitialized = false;
    }
  }

  bool CameraController::isInitialized() {
    return mSdkInitialized;
  }

  bool CameraController::startCameraListChangeListener() {
    if (!verifyCall(EdsSetCameraAddedHandler(CameraController::CameraAddedHandlerCallback, this))) {
      return false;
    }
    mCameraListTimer.setInterval(3000);
    connect(&mCameraListTimer, SIGNAL(timeout()), this, SLOT(updateCameraList()));
    mCameraListTimer.start();
    return true;
  }

  std::string CameraController::getErrorDescription() {
    return errorToString(getLastError());
  }

  EdsError CameraController::CameraAddedHandler() {
    updateCameraList();
    return EDS_ERR_OK;
  }

  EdsError CameraController::CameraAddedHandlerCallback(EdsVoid *inContext) {
    CameraController *cc = static_cast<CameraController *>(inContext);
    return cc->CameraAddedHandler();
  }

  void CameraController::updateCameraList() {
    auto newCameraList = std::make_shared<CameraList>();
    if (!mCameraList || (mCameraList->getCamerasInfo() != newCameraList->getCamerasInfo())) {
      mCameraList = newCameraList;
      emit camerasListChanged(mCameraList->getCamerasInfo());
    }
  }
}
