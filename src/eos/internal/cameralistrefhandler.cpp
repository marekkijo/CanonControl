#include "cameralistrefhandler.hpp"

#include <edsdk/EDSDK.h>

#include "utilities.hpp"

namespace EOS {
  namespace Internal {
    CameraListRefHandler::CameraListRefHandler()
    : mCameraListRef{nullptr}
    , mInitialized{verifyCall(EdsGetCameraList(&mCameraListRef))} {
    }

    CameraListRefHandler::~CameraListRefHandler() {
      if (mInitialized) {
        verifyCall(EdsRelease(mCameraListRef));
        mCameraListRef = nullptr;
        mInitialized = false;
      }
    }

    EdsCameraListRef CameraListRefHandler::getCameraListRef() {
      return mCameraListRef;
    }

    bool CameraListRefHandler::isInitialized() {
      return mInitialized;
    }
  }
}
