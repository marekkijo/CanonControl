#include "cameraimpl.hpp"

#include "camerarefhandler.hpp"
#include "../exceptions.hpp"

namespace EOS {
  namespace Internal {
    CameraImpl::CameraImpl(const std::shared_ptr<CameraListRefHandler> &cameraListRefHandler, std::size_t index)
      : mCameraRefHandler{std::make_unique<CameraRefHandler>(cameraListRefHandler, index)} {
      if (!mCameraRefHandler->isInitialized()) {
        throw InitializationException();
      }
    }

    CameraImpl::~CameraImpl() {
    }
  }
}
