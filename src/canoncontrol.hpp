#pragma once

#include <vector>

#include <QtWidgets/QMainWindow>

#include "ui_canoncontrol.h"
#include "cameraselection.hpp"
#include "eos/cameracontroller.hpp"
#include "eos/deviceinfo.hpp"

class CanonControl : public QMainWindow {
  Q_OBJECT

public:
  CanonControl(QWidget *parent = Q_NULLPTR);
  void showEvent(QShowEvent *event) override;

private:
  Ui::CanonControlClass ui;
  CameraSelection mCameraSelection;
  EOS::CameraController mCameraController;

public slots:
  void connectionButtonClicked();
  void camerasListUpdate(const std::vector<EOS::DeviceInfo> &camerasList);
};
