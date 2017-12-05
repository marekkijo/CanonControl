#include "canoncontrol.hpp"

#include "ui_canoncontrol.h"
#include <QtWidgets/QMessageBox>

#include "cameraselection.hpp"

#include "eos/sdk.hpp"
#include "eos/exceptions.hpp"

CanonControl::CanonControl(QWidget *parent)
  : QMainWindow(parent)
  , mUi{std::make_unique<Ui::CanonControlClass>()}
  , mCameraSelection{nullptr}
  , mSDK{nullptr} {
  mUi->setupUi(this);
  mUi->statusBar->showMessage("Disconnected");
}

CanonControl::~CanonControl() {
}

bool CanonControl::init() {
  mCameraSelection = std::make_shared<CameraSelection>(this);

  try {
    mSDK = std::make_unique<EOS::SDK>();
  } catch (const EOS::InitializationException &exception) {
    QMessageBox::critical(this, QString("Critical error"), exception.what());
    return false;
  }

  mSDK->registerDeviceConnectionStatusListener(std::weak_ptr<EOS::DeviceConnectionStatusListener>{shared_from_this()});
  mSDK->registerDeviceListChangedListener(std::weak_ptr<EOS::DeviceListChangedListener>{mCameraSelection});

  return true;
}

void CanonControl::deviceConnected(std::shared_ptr<EOS::Device>& device) {
}

void CanonControl::deviceDisconnected(std::shared_ptr<EOS::Device>& device) {
}

void CanonControl::connectionButtonClicked() {
  if (mCameraSelection->exec()) {
    QMessageBox::critical(this, QString("Critical error"), QString::number(mCameraSelection->getSelectedCameraIndex()));
  }
}
