#pragma once

#include <cstddef>

namespace EOS {
  namespace Internal {
    class SDKRefHandler {
    public:
      SDKRefHandler();
      ~SDKRefHandler();
      bool isInitialized();

    private:
      static std::size_t mInstanceCounter;
      static bool mInitialized;
    };
  }
}
