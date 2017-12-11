#include "cameralist.hpp"

#include <edsdk/EDSDK.h>

#include "cameralistrefhandler.hpp"
#include "camerarefhandler.hpp"
#include "utilities.hpp"
#include "../exceptions.hpp"
#include "../camerainfo.hpp"

namespace EOS {
  namespace Internal {
    CameraList::CameraList()
    : mCameraListRefHandler{std::make_shared<CameraListRefHandler>()}
    , mCamerasInfo{} {
      if (!mCameraListRefHandler->isInitialized()) {
        throw InitializationException();
      }

      init();
    }

    CameraList::~CameraList() {
    }

    const std::vector<CameraInfo> &CameraList::getCamerasInfo() {
      return mCamerasInfo;
    }

    void CameraList::init() {
      EdsUInt32 cameraCount;

      if (!Internal::verifyCall(EdsGetChildCount(mCameraListRefHandler->getCameraListRef(), &cameraCount))) {
        throw InitializationException();
      }

      for (std::size_t i = 0; i < cameraCount; i ++) {
        CameraRefHandler cameraRefHandler(mCameraListRefHandler, i);
        if (!cameraRefHandler.isInitialized()) {
          throw InitializationException();
        }

        EdsDeviceInfo deviceInfo;
        if (!Internal::verifyCall(EdsGetDeviceInfo(cameraRefHandler.getCameraRef(), &deviceInfo))) {
          throw InitializationException();
        }

        const CameraInfo cameraInfo{i, deviceInfo.szPortName, deviceInfo.szDeviceDescription, deviceInfo.deviceSubType, deviceInfo.reserved};
        mCamerasInfo.push_back(cameraInfo);
      }
    }
  }
}
