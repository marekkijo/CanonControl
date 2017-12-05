#pragma once

#include <exception>
#include <string>

namespace EOS {
  class InitializationException : public std::exception {
  public:
    InitializationException();
    const char *what() const override;

  private:
    const std::string mWhat;
  };
}
