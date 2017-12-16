#pragma once

#include <vector>
#include <memory>

#include <optional>

#include <QtWidgets/QMainWindow>

#include "eos/cameraconnectionstatuslistener.hpp"
#include "eos/cameraparameterchangedlistener.hpp"

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
                   , public EOS::CameraConnectionStatusListener
                   , public EOS::CameraParameterChangedListener {
  Q_OBJECT

public:
  explicit CanonControl(QWidget *parent = nullptr);
  ~CanonControl() override;
  bool init();

public: // EOS::CameraConnectionStatusListener
  void cameraConnected(const std::shared_ptr<EOS::Camera> &camera) override;
  void cameraDisconnected(const std::shared_ptr<EOS::Camera> &camera) override;

public: // EOS::CameraParameterChangedListener
  void cameraPropertyUpdate_isoSpeed(std::uint32_t value) override;

private:
  struct CameraPropertiesUpdateSet {
    template<typename PropertyType>
    struct Set {
      std::optional<PropertyType> value;
      bool sent;
    };

    Set<std::uint32_t> isoSpeed;
  };

  const std::unique_ptr<Ui::CanonControlClass> mUi;
  std::unique_ptr<QTimer> mRefreshTimer;
  std::unique_ptr<CameraSelection> mCameraSelection;
  std::shared_ptr<EOS::SDK> mSDK;
  std::shared_ptr<EOS::Camera> mConnectedCamera;
  CameraPropertiesUpdateSet mCameraPropertiesUpdateSet;

  void cameraConnectionUiUpdate();

public slots:
  void refreshNotify();
  void connectionButtonClicked();
  void uiCameraPropertyChanged_isoSpeed(int value);
};
