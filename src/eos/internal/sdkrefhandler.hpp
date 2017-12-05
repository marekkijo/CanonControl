#pragma once

#include <atomic>

namespace EOS {
  namespace Internal {
    class SDKRefHandler {
    public:
      SDKRefHandler();
      ~SDKRefHandler();
      bool isInitialized();

    private:
      static std::atomic_size_t mInstanceCounter;
      static std::atomic_bool mInitialized;
    };
  }
}
