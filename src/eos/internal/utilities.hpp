#pragma once

#include <string>

#include <edsdk/EDSDKTypes.h>

namespace EOS {
  namespace Internal {
    std::string errorToString(EdsError error);
    EdsError getLastError();
    bool verifyCall(EdsError error);
    bool verifyRefCountCall(EdsUInt32 result);
  }
}
