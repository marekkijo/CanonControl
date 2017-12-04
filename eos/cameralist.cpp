#include "cameralist.hpp"

#include <string>

#include "utilities.hpp"

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

  const std::vector<CameraInfo>& CameraList::getCamerasInfo() {
    return mCamerasInfo;
  }

  bool CameraList::init() {
    if (!verifyCall(EdsGetCameraList(&mCameraListRef))) {
      return false;
    }

    if (!verifyCall(EdsGetChildCount(mCameraListRef, &mCameraCount))) {
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

    return verifyCall(EdsRelease(cameraListRefToTerminate));
  }

  bool CameraList::fillCameraList() {
    EdsCameraRef cameraRef = nullptr;
    EdsDeviceInfo deviceInfo;

    for (EdsUInt32 i = 0; i < mCameraCount; i ++) {
      if (!verifyCall(EdsGetChildAtIndex(mCameraListRef, i, &cameraRef))) {
        return false;
      }

      if (!verifyCall(EdsGetDeviceInfo(cameraRef, &deviceInfo))) {
        EdsRelease(cameraRef);
        return false;
      }

      CameraInfo cameraInfo{i, deviceInfo.szPortName, deviceInfo.szDeviceDescription, deviceInfo.deviceSubType, deviceInfo.reserved};
      mCamerasInfo.push_back(cameraInfo);

      if (!verifyCall(EdsRelease(cameraRef))) {
        return false;
      }
      cameraRef = nullptr;
    }

    return true;
  }
}