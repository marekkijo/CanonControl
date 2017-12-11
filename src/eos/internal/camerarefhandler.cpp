#include "camerarefhandler.hpp"

#include <edsdk/EDSDK.h>

#include "cameralistrefhandler.hpp"
#include "utilities.hpp"

namespace EOS {
  namespace Internal {
    CameraRefHandler::CameraRefHandler(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index)
    : mCameraListRefHandler{cameraListRefHandler}
    , mCameraRef{nullptr}
    , mInitialized{Internal::verifyCall(EdsGetChildAtIndex(mCameraListRefHandler->getCameraListRef(), index, &mCameraRef))} {
    }

    CameraRefHandler::~CameraRefHandler() {
      if (mInitialized) {
        Internal::verifyCall(EdsRelease(mCameraRef));
        mCameraRef = nullptr;
        mInitialized = false;
      }
    }

    EdsCameraRef CameraRefHandler::getCameraRef() {
      return mCameraRef;
    }

    bool CameraRefHandler::isInitialized() {
      return mInitialized;
    }
  }
}
