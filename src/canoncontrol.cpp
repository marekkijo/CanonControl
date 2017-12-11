#include "canoncontrol.hpp"

#include "ui_canoncontrol.h"
#include <QtWidgets/QMessageBox>
#include <QTimer>

#include "eos/exceptions.hpp"
#include "eos/sdk.hpp"

#include "cameraselection.hpp"

CanonControl::CanonControl(QWidget *parent)
  : QMainWindow(parent)
  , mUi{std::make_unique<Ui::CanonControlClass>()}
  , mRefreshTimer{std::make_unique<QTimer>()}
  , mCameraSelection{nullptr}
  , mSDK{nullptr} {
  mUi->setupUi(this);
  mUi->statusBar->showMessage("Disconnected");
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

void CanonControl::cameraConnected(std::shared_ptr<EOS::Camera>& camera) {
}

void CanonControl::cameraDisconnected(std::shared_ptr<EOS::Camera>& camera) {
}

void CanonControl::refreshNotify() {
  mSDK->refreshNotify();
}

void CanonControl::connectionButtonClicked() {
  if (mCameraSelection->exec()) {
    mUi->connectPushButton->setEnabled(false);
    mSDK->connectCamera(mCameraSelection->getSelectedCameraIndex());
  }
}
