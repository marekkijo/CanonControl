#pragma once

#include <vector>

#include <QtWidgets/QDialog>

#include "ui_cameraselection.h"
#include "eos/camerainfo.hpp"

class CameraSelection : public QDialog {
  Q_OBJECT

public:
  CameraSelection(QWidget *parent = Q_NULLPTR);
  void showEvent(QShowEvent *event) override;
  EdsUInt32 getSelectedCameraIndex();

private:
  Ui::CameraSelectionClass ui;
  EdsUInt32 mSelectedCameraIndex;

  void resetCamerasTableWidget();

public slots:
  void camerasListUpdate(const std::vector<EOS::CameraInfo> &camerasList);
};
