#include "sdkrefhandler.hpp"

#include <edsdk/EDSDK.h>

#include "utilities.hpp"

namespace EOS {
  namespace Internal {
    SDKRefHandler::SDKRefHandler() {
      mInstanceCounter ++;

      if (mInstanceCounter == 1) {
        mInitialized = Internal::verifyCall(EdsInitializeSDK());
      }
    }

    SDKRefHandler::~SDKRefHandler() {
      if (mInstanceCounter == 1 && mInitialized) {
        Internal::verifyCall(EdsTerminateSDK());
        mInitialized = false;
      }

      mInstanceCounter --;
    }

    bool SDKRefHandler::isInitialized() {
      return mInitialized;
    }

    std::size_t SDKRefHandler::mInstanceCounter{0};
    bool SDKRefHandler::mInitialized{false};
  }
}
