#pragma once

#include <memory>

namespace EOS {
  namespace Internal {
    class ControllerImpl;
  }

  class Controller {
  public:
    Controller();
    ~Controller();

  private:
    const std::unique_ptr<Internal::ControllerImpl> pImpl;
  };
}
