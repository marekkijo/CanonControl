#pragma once

#include <vector>

namespace EOS {
  class CameraInfo;

  class CameraListChangedListener {
  public:
    virtual ~CameraListChangedListener() = default;
    virtual void cameraListChanged(const std::vector<CameraInfo> &cameraList) = 0;
  };
}
