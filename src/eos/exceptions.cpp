#include "exceptions.hpp"

#include "internal/utilities.hpp"

namespace EOS {
  InitializationException::InitializationException()
    : mWhat{"InitializationException: " + Internal::errorToString(Internal::getLastError())} {
  }

  const char *InitializationException::what() const {
    return mWhat.c_str();
  }
}
