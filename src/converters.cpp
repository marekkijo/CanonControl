#include "converters.hpp"

#include <array>

#include "eos/enums.hpp"

namespace Converters {
  namespace ISO {
    const static int kMinValue{0};
    const static int kMaxValue{29};
    const static std::array<std::string, 30> kValueToString{
      "A", "L", "100", "125", "160", "200", "250", "320",
      "400", "500", "640", "800", "1000", "1250", "1600",
      "2000", "2500", "3200", "4000", "5000", "6400", "8000",
      "10000", "12800", "16000", "20000", "25600", "32000", "H1", "H2"
    };

    int minValue() {
      return kMinValue;
    }

    int maxValue() {
      return kMaxValue;
    }

    std::string valueToString(int value) {
      if (value < minValue() || value > maxValue())
        throw std::invalid_argument("Converters::ISO::valueToString()");
      return kValueToString[value];
    }

    int stringToValue(std::string _string) {
      auto it = std::find(kValueToString.begin(), kValueToString.end(), _string);
      if (it == kValueToString.end())
        throw std::invalid_argument("Converters::ISO::stringToValue()");
      return std::distance(kValueToString.begin(), it);
    }

    EOS::ISOValue valueToEnum(int value) {
      if (value < minValue() || value > maxValue())
        throw std::invalid_argument("Converters::ISO::valueToEnum()");

      return static_cast<EOS::ISOValue>(value);
    }

    int enumToValue(EOS::ISOValue _enum) {
      return static_cast<int>(_enum);
    }
  }
}
