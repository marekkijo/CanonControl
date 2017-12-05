#include "cameralist.hpp"

#include <string>

#include "internal/utilities.hpp"

namespace EOS {
  CameraList::CameraList()
    : mCameraListRef{nullptr}
    , mCameraCount{0}
    , mCamerasInfo{} {
    init();
  }

  CameraList::~CameraList() {
    terminate();
  }

  const std::vector<DeviceInfo>& CameraList::getCamerasInfo() {
    return mCamerasInfo;
  }

  bool CameraList::init() {
    if (!Internal::verifyCall(EdsGetCameraList(&mCameraListRef))) {
      return false;
    }

    if (!Internal::verifyCall(EdsGetChildCount(mCameraListRef, &mCameraCount))) {
      terminate();
      return false;
    }

    fillCameraList();

    return false;
  }

  bool CameraList::terminate() {
    if (!mCameraListRef)
      return true;

    EdsCameraListRef cameraListRefToTerminate = mCameraListRef;
    mCameraListRef = nullptr;
    mCameraCount = 0;
    mCamerasInfo.clear();

    return Internal::verifyCall(EdsRelease(cameraListRefToTerminate));
  }

  bool CameraList::fillCameraList() {
    EdsCameraRef cameraRef = nullptr;
    EdsDeviceInfo deviceInfo;

    for (EdsUInt32 i = 0; i < mCameraCount; i ++) {
      if (!Internal::verifyCall(EdsGetChildAtIndex(mCameraListRef, i, &cameraRef))) {
        return false;
      }

      if (!Internal::verifyCall(EdsGetDeviceInfo(cameraRef, &deviceInfo))) {
        EdsRelease(cameraRef);
        return false;
      }

      DeviceInfo cameraInfo{i, deviceInfo.szPortName, deviceInfo.szDeviceDescription, deviceInfo.deviceSubType, deviceInfo.reserved};
      mCamerasInfo.push_back(cameraInfo);

      if (!Internal::verifyCall(EdsRelease(cameraRef))) {
        return false;
      }
      cameraRef = nullptr;
    }

    return true;
  }
}