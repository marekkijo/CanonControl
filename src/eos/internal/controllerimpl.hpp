#pragma once

#include <memory>

namespace EOS {
  namespace Internal {
    class SDKRefHandler;

    class ControllerImpl {
    public:
      ControllerImpl();
      ~ControllerImpl();

    private:
      std::unique_ptr<SDKRefHandler> mSDKRefHandler;
    };
  }
}
