#pragma once

#include <QtWidgets/QSpinBox>

class IsoSpinBox : public QSpinBox {
  Q_OBJECT

public:
  IsoSpinBox(QWidget *parent = Q_NULLPTR);
  QString IsoSpinBox::textFromValue(int value) const override;
};
