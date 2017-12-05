#pragma once

#include <vector>

#include <edsdk/EDSDK.h>
#include <edsdk/EDSDKTypes.h>
#include <edsdk/EDSDKErrors.h>

#include "deviceinfo.hpp"

namespace EOS {
  class CameraList {
  public:
    CameraList();
    ~CameraList();
    const std::vector<DeviceInfo> &getCamerasInfo();

  private:
    EdsCameraListRef mCameraListRef;
    EdsUInt32 mCameraCount;
    std::vector<DeviceInfo> mCamerasInfo;

    bool init();
    bool terminate();
    bool fillCameraList();
  };
}
