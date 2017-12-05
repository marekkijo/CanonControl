#include "deviceinfo.hpp"

namespace EOS {
  bool operator==(const DeviceInfo& lhs, const DeviceInfo& rhs) {
    return
      lhs.index == rhs.index &&
      lhs.portName == rhs.portName &&
      lhs.description == rhs.description &&
      lhs.subType == rhs.subType;
  }
}
