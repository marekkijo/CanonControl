#include "camerainfo.hpp"

namespace EOS {
  bool operator==(const CameraInfo& lhs, const CameraInfo& rhs) {
    return
      lhs.index == rhs.index &&
      lhs.portName == rhs.portName &&
      lhs.description == rhs.description &&
      lhs.subtype == rhs.subtype;
  }
}
