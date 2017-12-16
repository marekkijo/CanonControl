#include "camerarefhandler.hpp"

#include <edsdk/EDSDK.h>

#include "cameralistrefhandler.hpp"
#include "utilities.hpp"

namespace EOS {
  namespace Internal {
    CameraRefHandler::CameraRefHandler(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index) {
      if (!mCameraListRefHandler) {
        mCameraListRefHandler = cameraListRefHandler;
      }

      if (mCameraRef) {
        verifyRefCountCall(EdsRetain(mCameraRef));
      } else {
        verifyCall(EdsGetChildAtIndex(mCameraListRefHandler->getCameraListRef(), index, &mCameraRef));
      }
    }

    CameraRefHandler::~CameraRefHandler() {
      const EdsUInt32 refCount = EdsRelease(mCameraRef);
      verifyRefCountCall(refCount);
      if (refCount == 0) {
        mCameraRef = nullptr;
      }
    }

    EdsCameraRef CameraRefHandler::getCameraRef() {
      return mCameraRef;
    }

    bool CameraRefHandler::isInitialized() {
      return !!mCameraRef;
    }

    std::shared_ptr<CameraListRefHandler> CameraRefHandler::mCameraListRefHandler{nullptr};
    EdsCameraRef CameraRefHandler::mCameraRef{nullptr};
  }
}
