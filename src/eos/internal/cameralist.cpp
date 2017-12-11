#include "cameralist.hpp"

#include <edsdk/EDSDK.h>

#include "cameralistrefhandler.hpp"
#include "camerarefhandler.hpp"
#include "utilities.hpp"
#include "cameraimpl.hpp"
#include "../exceptions.hpp"
#include "../camerainfo.hpp"

namespace EOS {
  namespace Internal {
    CameraList::CameraList()
      : mCameraListRefHandler{std::make_shared<CameraListRefHandler>()}
      , mCamerasInfo{}
      , mConnectedCamera{nullptr} {
      if (!mCameraListRefHandler->isInitialized()) {
        throw InitializationException();
      }

      init();
    }

    CameraList::~CameraList() {
    }

    const std::vector<CameraInfo> &CameraList::getCamerasInfo() const {
      return mCamerasInfo;
    }

    const std::shared_ptr<Camera> &CameraList::getConnectedCamera() const {
      return mConnectedCamera;
    }

    const std::shared_ptr<Camera> &CameraList::connectCamera(std::size_t index) {
      if (mConnectedCamera) {
        disconnectCamera(mConnectedCamera);
      }

      const std::shared_ptr<CameraImpl> connectedCameraImpl{std::make_shared<CameraImpl>(mCameraListRefHandler, index, mCamerasInfo[index])};
      if (connectedCameraImpl->isInitialized()) {
        return mConnectedCamera = connectedCameraImpl;
      }

      return mConnectedCamera;
    }

    void CameraList::disconnectCamera(const std::shared_ptr<Camera> &connectedCamera) {
      if (mConnectedCamera == connectedCamera) {
        mConnectedCamera.reset();
      }
    }

    bool CameraList::reassignConnectedCamera(const std::shared_ptr<CameraList> &cameraList) {
      if (!cameraList || !cameraList->getConnectedCamera()) {
        return true;
      }

      EdsUInt32 cameraCount;
      if (!verifyCall(EdsGetChildCount(mCameraListRefHandler->getCameraListRef(), &cameraCount))) {
        cameraCount = 0;
      }

      const std::shared_ptr<CameraImpl> connectedCameraImpl = std::dynamic_pointer_cast<CameraImpl>(cameraList->mConnectedCamera);

      for (std::size_t i = 0; i < cameraCount; i ++) {
        CameraRefHandler cameraRefHandler(mCameraListRefHandler, i);
        if (!cameraRefHandler.isInitialized()) {
          continue;
        }

        if (cameraRefHandler.getCameraRef() == connectedCameraImpl->getCameraRef()) {
          if (mConnectedCamera) {
            disconnectCamera(mConnectedCamera);
          }

          mConnectedCamera = cameraList->mConnectedCamera;
          cameraList->mConnectedCamera.reset();
          return true;
        }
      }

      return false;
    }

    void CameraList::init() {
      EdsUInt32 cameraCount;

      if (!verifyCall(EdsGetChildCount(mCameraListRefHandler->getCameraListRef(), &cameraCount))) {
        throw InitializationException();
      }

      for (std::size_t i = 0; i < cameraCount; i ++) {
        CameraRefHandler cameraRefHandler(mCameraListRefHandler, i);
        if (!cameraRefHandler.isInitialized()) {
          throw InitializationException();
        }

        EdsDeviceInfo deviceInfo;
        if (!verifyCall(EdsGetDeviceInfo(cameraRefHandler.getCameraRef(), &deviceInfo))) {
          throw InitializationException();
        }

        const CameraInfo cameraInfo{i, deviceInfo.szPortName, deviceInfo.szDeviceDescription, deviceInfo.deviceSubType, deviceInfo.reserved};
        mCamerasInfo.push_back(cameraInfo);
      }
    }
  }
}
