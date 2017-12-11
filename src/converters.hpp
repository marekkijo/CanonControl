#pragma once

#include <string>

namespace EOS {
  enum class ISOValue;
}

namespace Converters {
  namespace ISO {
    int minValue();
    int maxValue();
    std::string valueToString(int value);
    int stringToValue(std::string str);
    EOS::ISOValue valueToEnum(int value);
    int enumToValue(EOS::ISOValue iso_value);
  }
}