#include "cameraimpl.hpp"

#include <edsdk/EDSDK.h>

#include "camerarefhandler.hpp"
#include "utilities.hpp"
#include "../exceptions.hpp"

namespace EOS {
  namespace Internal {
    CameraImpl::CameraImpl(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index, const CameraInfo &cameraInfo)
      : mCameraRefHandler{std::make_unique<CameraRefHandler>(cameraListRefHandler, index)}
      , mCameraInfo{cameraInfo}
      , mInitialized{false} {
      if (!mCameraRefHandler->isInitialized()) {
        throw InitializationException();
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

    const CameraInfo & CameraImpl::getCameraInfo() const {
      return mCameraInfo;
    }
  }
}
