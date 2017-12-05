#pragma once

#include <vector>
#include <memory>

#include <QtWidgets/QMainWindow>

#include "eos/deviceconnectionstatuslistener.hpp"

namespace Ui {
  class CanonControlClass;
}

class CameraSelection;

namespace EOS {
  class SDK;
  class Device;
}

class CanonControl : public QMainWindow
                   , public std::enable_shared_from_this<CanonControl>
                   , public EOS::DeviceConnectionStatusListener {
  Q_OBJECT

public:
  CanonControl(QWidget *parent = Q_NULLPTR);
  ~CanonControl() override;
  bool init();

public: // EOS::DeviceConnectionStatusListener
  void deviceConnected(std::shared_ptr<EOS::Device> &device) override;
  void deviceDisconnected(std::shared_ptr<EOS::Device> &device) override;

private:
  const std::unique_ptr<Ui::CanonControlClass> mUi;
  std::shared_ptr<CameraSelection> mCameraSelection;
  std::shared_ptr<EOS::SDK> mSDK;

public slots:
  void connectionButtonClicked();
};
