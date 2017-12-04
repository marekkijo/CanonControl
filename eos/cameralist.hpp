#pragma once

#include <vector>

#include <edsdk/EDSDK.h>
#include <edsdk/EDSDKTypes.h>
#include <edsdk/EDSDKErrors.h>

#include "camerainfo.hpp"

namespace EOS {
  class CameraList {
  public:
    CameraList();
    ~CameraList();
    const std::vector<CameraInfo> &getCamerasInfo();

  private:
    EdsCameraListRef mCameraListRef;
    EdsUInt32 mCameraCount;
    std::vector<CameraInfo> mCamerasInfo;

    bool init();
    bool terminate();
    bool fillCameraList();
  };
}
