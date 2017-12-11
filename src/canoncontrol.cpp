#include "canoncontrol.hpp"

#include "ui_canoncontrol.h"
#include <QtWidgets/QMessageBox>
#include <QTimer>

#include "eos/exceptions.hpp"
#include "eos/sdk.hpp"
#include "eos/camera.hpp"
#include "eos/camerainfo.hpp"

#include "cameraselection.hpp"

CanonControl::CanonControl(QWidget *parent)
  : QMainWindow(parent)
  , mUi{std::make_unique<Ui::CanonControlClass>()}
  , mRefreshTimer{std::make_unique<QTimer>()}
  , mCameraSelection{nullptr}
  , mSDK{nullptr}
  , mConnectedCamera{nullptr} {
  mUi->setupUi(this);
  cameraConnectionUiUpdate();
}

CanonControl::~CanonControl() {
  mSDK->unregisterCameraConnectionStatusListener(this);
}

bool CanonControl::init() {
  try {
    mSDK = std::make_unique<EOS::SDK>();
  } catch (const EOS::InitializationException &exception) {
    QMessageBox::critical(this, QString("Critical error"), exception.what());
    return false;
  }

  mCameraSelection = std::make_unique<CameraSelection>(mSDK, this);

  mSDK->registerCameraConnectionStatusListener(this);

  connect(mRefreshTimer.get(), SIGNAL(timeout()), this, SLOT(refreshNotify()));
  mRefreshTimer->start(3000);

  mSDK->setCameraAddedHandler();

  return true;
}

void CanonControl::cameraConnected(const std::shared_ptr<EOS::Camera> &camera) {
  mConnectedCamera = camera;
  cameraConnectionUiUpdate();
  mUi->connectPushButton->setEnabled(true);
}

void CanonControl::cameraDisconnected(const std::shared_ptr<EOS::Camera> &camera) {
  if (mConnectedCamera != camera) {
    return;
  }

  mConnectedCamera.reset();
  cameraConnectionUiUpdate();
  mUi->connectPushButton->setEnabled(true);
}

void CanonControl::cameraConnectionUiUpdate() {
  if (mConnectedCamera) {
    mUi->connectPushButton->setText(QString(tr("&Disconnect")));
    mUi->statusBar->showMessage(tr("Connected: ") + QString::fromStdString(mConnectedCamera->getCameraInfo().description));
  } else {
    mUi->connectPushButton->setText(QString(tr("&Connect")));
    mUi->statusBar->showMessage(tr("Disconnected"));
  }
}

void CanonControl::refreshNotify() {
  mSDK->refreshNotify();
}

void CanonControl::connectionButtonClicked() {
  if (mConnectedCamera) {
    mUi->connectPushButton->setEnabled(false);
    mSDK->disconnectCamera(mConnectedCamera);
  } else if (mCameraSelection->exec()) {
    mUi->connectPushButton->setEnabled(false);
    mSDK->connectCamera(mCameraSelection->getSelectedCameraIndex());
  }
}
