#pragma once

#include <string>

#include "eos/enums.hpp"

namespace Converters {
  namespace ISO {
    int minValue();
    int maxValue();
    std::string valueToString(int value);
    int stringToValue(std::string _string);
    EOS::ISOValue valueToEnum(int value);
    int enumToValue(EOS::ISOValue _enum);
  }
}