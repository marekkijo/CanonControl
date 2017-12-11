#include "sdkimpl.hpp"

#include <edsdk/EDSDK.h>

#include "sdkrefhandler.hpp"
#include "utilities.hpp"
#include "cameralist.hpp"
#include "../exceptions.hpp"
#include "../cameraconnectionstatuslistener.hpp"
#include "../cameralistchangedlistener.hpp"
#include "../camerainfo.hpp"

namespace EOS {
  namespace Internal {
    SDKImpl::SDKImpl()
    : mSDKRefHandler{std::make_unique<SDKRefHandler>()}
    , mCameraList{nullptr}
    , mCameraListChangedListeners{}
    , mCameraConnectionStatusListeners{} {
      if (!mSDKRefHandler->isInitialized()) {
        throw InitializationException();
      }
    }

    SDKImpl::~SDKImpl() {
    }

    void SDKImpl::registerCameraListChangedListener(CameraListChangedListener *cameraListChangedListener) {
      mCameraListChangedListeners.insert(cameraListChangedListener);
    }

    void SDKImpl::unregisterCameraListChangedListener(CameraListChangedListener *cameraListChangedListener) {
      mCameraListChangedListeners.erase(cameraListChangedListener);
    }

    void SDKImpl::registerCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener) {
      mCameraConnectionStatusListeners.insert(cameraConnectionStatusListener);
    }

    void SDKImpl::unregisterCameraConnectionStatusListener(CameraConnectionStatusListener *cameraConnectionStatusListener) {
      mCameraConnectionStatusListeners.erase(cameraConnectionStatusListener);
    }

    void SDKImpl::refreshNotify() {
      cameraAddedHandler();
    }

    void SDKImpl::setCameraAddedHandler() {
      if (!verifyCall(EdsSetCameraAddedHandler(SDKImpl::cameraAddedHandler, this))) {
        throw InitializationException();
      }
    }

    void SDKImpl::clearCameraAddedHandler() {
      if (!verifyCall(EdsSetCameraAddedHandler(nullptr, nullptr))) {
        throw InitializationException();
      }
    }

    void SDKImpl::connectCamera(size_t index) {
    }

    void SDKImpl::notifyCameraListChangedListeners(const std::vector<CameraInfo> &cameraList) {
      for (const auto &listener : mCameraListChangedListeners) {
        listener->cameraListChanged(cameraList);
      }
    }

    void SDKImpl::cameraAddedHandler() {
      std::shared_ptr<CameraList> newCameraList{std::make_shared<CameraList>()};
      if (!mCameraList){
        mCameraList = newCameraList;
        if (!mCameraList->getCamerasInfo().empty()){
          notifyCameraListChangedListeners(mCameraList->getCamerasInfo());
        }
      }

      if (mCameraList->getCamerasInfo() != newCameraList->getCamerasInfo()) {
        // TODO: verify camera disconnected
        // if yes notifyCameraConnectionStatusListeners
        // else move camera connectrion to newCameraList 

        mCameraList = newCameraList;
        notifyCameraListChangedListeners(mCameraList->getCamerasInfo());
      }
    }

    EdsError SDKImpl::cameraAddedHandler(EdsVoid *inContext) {
      SDKImpl *impl = static_cast<SDKImpl *>(inContext);
      impl->cameraAddedHandler();
      return EDS_ERR_OK;
    }
  }
}
