#pragma once

#include <string>

#include <edsdk/EDSDK.h>
#include <edsdk/EDSDKTypes.h>
#include <edsdk/EDSDKErrors.h>

namespace EOS {
  std::string errorToString(EdsError error);
  EdsError getLastError();
  bool verifyCall(EdsError error);
}
