#pragma once

#include <memory>
#include <vector>
#include <cstddef>

#include <QtWidgets/QDialog>

#include "eos/devicelistchangedlistener.hpp"

namespace Ui {
  class CameraSelectionClass;
}

namespace EOS {
  class DeviceInfo;
}

class CameraSelection : public QDialog
                      , public EOS::DeviceListChangedListener {
  Q_OBJECT

public:
  CameraSelection(QWidget *parent = Q_NULLPTR);
  ~CameraSelection() override;
  void showEvent(QShowEvent *event) override;
  std::size_t getSelectedCameraIndex();

public: // EOS::DeviceListChangedListener
  void deviceListChanged(const std::vector<EOS::DeviceInfo> &deviceList) override;

private:
  const std::unique_ptr<Ui::CameraSelectionClass> mUi;
  std::size_t mSelectedCameraIndex;
  std::vector<EOS::DeviceInfo> mDeviceList;

  void refreshView();
  void resetCamerasTableWidget();
};
