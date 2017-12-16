#include "cameralistrefhandler.hpp"

#include <edsdk/EDSDK.h>

#include "utilities.hpp"

namespace EOS {
  namespace Internal {
    CameraListRefHandler::CameraListRefHandler() {
      if (mCameraListRef) {
        verifyRefCountCall(EdsRetain(mCameraListRef));
      } else {
        verifyCall(EdsGetCameraList(&mCameraListRef));
      }
    }

    CameraListRefHandler::~CameraListRefHandler() {
      const EdsUInt32 refCount = EdsRelease(mCameraListRef);
      verifyRefCountCall(refCount);
      if (refCount == 0) {
        mCameraListRef = nullptr;
      }
    }

    EdsCameraListRef CameraListRefHandler::getCameraListRef() {
      return mCameraListRef;
    }

    bool CameraListRefHandler::isInitialized() {
      return !!mCameraListRef;
    }

    EdsCameraListRef CameraListRefHandler::mCameraListRef{nullptr};
  }
}
