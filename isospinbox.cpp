#include "isospinbox.hpp"

#include <array>

IsoSpinBox::IsoSpinBox(QWidget *parent)
  : QSpinBox(parent) {
}

QString IsoSpinBox::textFromValue(int value) const {
  static std::array<QString, 30> valueToString{
    "A", "L", "100", "125", "160", "200", "250", "320",
    "400", "500", "640", "800", "1000", "1250", "1600",
    "2000", "2500", "3200", "4000", "5000", "6400", "8000",
    "10000", "12800", "16000", "20000", "25600", "32000", "H1", "H2"
  };
  if (value < valueToString.size())
    return valueToString[value];
  return QString::number(value);
}