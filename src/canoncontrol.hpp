#pragma once

#include <vector>
#include <memory>

#include <QtWidgets/QMainWindow>

#include "eos/cameraconnectionstatuslistener.hpp"

namespace Ui {
  class CanonControlClass;
}

class QTimer;
class CameraSelection;

namespace EOS {
  class SDK;
  class Camera;
}

class CanonControl : public QMainWindow
                   , public EOS::CameraConnectionStatusListener {
  Q_OBJECT

public:
  explicit CanonControl(QWidget *parent = nullptr);
  ~CanonControl() override;
  bool init();

public: // EOS::CameraConnectionStatusListener
  void cameraConnected(std::shared_ptr<EOS::Camera> &camera) override;
  void cameraDisconnected(std::shared_ptr<EOS::Camera> &camera) override;

private:
  const std::unique_ptr<Ui::CanonControlClass> mUi;
  const std::unique_ptr<QTimer> mRefreshTimer;
  std::unique_ptr<CameraSelection> mCameraSelection;
  std::shared_ptr<EOS::SDK> mSDK;

public slots:
  void refreshNotify();
  void connectionButtonClicked();
};
