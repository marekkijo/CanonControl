#include "controller.hpp"

#include "exceptions.hpp"
#include "internal/controllerimpl.hpp"

namespace EOS {
  std::unique_ptr<Internal::ControllerImpl> controllerImplFactory() {
    std::unique_ptr<Internal::ControllerImpl> impl;

    try {
      impl = std::make_unique<Internal::ControllerImpl>();
    } catch (const InitializationException &) {
      return nullptr;
    }

    return impl;
  }
  Controller::Controller()
    : pImpl{controllerImplFactory()} {
  }

  Controller::~Controller() {
  }
}
