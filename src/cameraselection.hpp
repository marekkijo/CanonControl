#pragma once

#include <vector>

#include <QtWidgets/QDialog>

#include <edsdk/EDSDK.h>
#include <edsdk/EDSDKTypes.h>
#include <edsdk/EDSDKErrors.h>

#include "ui_cameraselection.h"
#include "eos/deviceinfo.hpp"

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
  void camerasListUpdate(const std::vector<EOS::DeviceInfo> &camerasList);
};
