#pragma once

#include <QtWidgets/QSpinBox>

class IsoSpinBox : public QSpinBox {
  Q_OBJECT

public:
  explicit IsoSpinBox(QWidget *parent = nullptr);
  QString IsoSpinBox::textFromValue(int value) const override;
};
