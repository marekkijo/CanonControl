#include "canoncontrol.hpp"

#include "ui_canoncontrol.h"
#include <QtWidgets/QMessageBox>
#include <QTimer>

#include "eos/exceptions.hpp"
#include "eos/sdk.hpp"
#include "eos/camera.hpp"
#include "eos/camerainfo.hpp"

#include "cameraselection.hpp"
#include <unordered_map>

CanonControl::CanonControl(QWidget *parent)
  : QMainWindow(parent)
  , mUi{std::make_unique<Ui::CanonControlClass>()}
  , mRefreshTimer{std::make_unique<QTimer>()}
  , mCameraSelection{nullptr}
  , mSDK{nullptr}
  , mConnectedCamera{nullptr}
  , mCameraPropertiesUpdateSet{} {
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
}

void CanonControl::cameraDisconnected(const std::shared_ptr<EOS::Camera> &camera) {
  if (mConnectedCamera != camera) {
    return;
  }

  mConnectedCamera.reset();
  cameraConnectionUiUpdate();
}

void CanonControl::cameraPropertyUpdate_isoSpeed(std::uint32_t value) {
  static std::unordered_map<std::uint32_t, int> valueMap{
    {0x00000000, 0},
    {0x00000040, 1},
    {0x00000048, 2},
    {0x0000004b, 3},
    {0x0000004d, 4},
    {0x00000050, 5},
    {0x00000053, 6},
    {0x00000055, 7},
    {0x00000058, 8},
    {0x0000005b, 9},
    {0x0000005d, 10},
    {0x00000060, 11},
    {0x00000063, 12},
    {0x00000065, 13},
    {0x00000068, 14},
    {0x0000006b, 15},
    {0x0000006d, 16},
    {0x00000070, 17},
    {0x00000073, 18},
    {0x00000075, 19},
    {0x00000078, 20},
    {0x0000007b, 21},
    {0x0000007d, 22},
    {0x00000080, 23},
    {0x00000083, 24},
    {0x00000085, 25},
    {0x00000088, 26},
    {0x0000008b, 27},
    {0x00000090, 28},
    {0x00000098, 29},
    {0x000000a0, 30},
    {0x000000a8, 31}};

  if (mCameraPropertiesUpdateSet.isoSpeed.sent) {
    if (mCameraPropertiesUpdateSet.isoSpeed.value.has_value() && mCameraPropertiesUpdateSet.isoSpeed.value.value() != value) {
      const std::uint32_t new_value = mCameraPropertiesUpdateSet.isoSpeed.value.value();
      mCameraPropertiesUpdateSet.isoSpeed.value.reset();
      mConnectedCamera->setCameraProperty_isoSpeed(new_value);
    } else {
      mCameraPropertiesUpdateSet.isoSpeed.sent = false;
    }
  } else {
    mUi->isoSlider->setValue(valueMap[value]);
  }
}

void CanonControl::cameraConnectionUiUpdate() {
  if (mConnectedCamera) {
    mUi->connectPushButton->setText(QString(tr("&Disconnect")));
    mUi->statusBar->showMessage(tr("Connected: ") + QString::fromStdString(mConnectedCamera->getCameraInfo().description));
    mUi->generalSettingsGroupBox->setEnabled(true);
    mUi->tabWidget->setEnabled(true);
  } else {
    mUi->connectPushButton->setText(QString(tr("&Connect")));
    mUi->statusBar->showMessage(tr("Disconnected"));
    mUi->generalSettingsGroupBox->setEnabled(false);
    mUi->tabWidget->setEnabled(false);
  }
  mUi->connectPushButton->setEnabled(true);
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
    mSDK->connectCamera(mCameraSelection->getSelectedCameraIndex(), this);
  }
}

void CanonControl::uiCameraPropertyChanged_isoSpeed(int value) {
  if (!mConnectedCamera) {
    return;
  }

  static std::unordered_map<int, std::uint32_t> valueMap{
    {0, 0x00000000},
    {1, 0x00000040},
    {2, 0x00000048},
    {3, 0x0000004b},
    {4, 0x0000004d},
    {5, 0x00000050},
    {6, 0x00000053},
    {7, 0x00000055},
    {8, 0x00000058},
    {9, 0x0000005b},
    {10, 0x0000005d},
    {11, 0x00000060},
    {12, 0x00000063},
    {13, 0x00000065},
    {14, 0x00000068},
    {15, 0x0000006b},
    {16, 0x0000006d},
    {17, 0x00000070},
    {18, 0x00000073},
    {19, 0x00000075},
    {20, 0x00000078},
    {21, 0x0000007b},
    {22, 0x0000007d},
    {23, 0x00000080},
    {24, 0x00000083},
    {25, 0x00000085},
    {26, 0x00000088},
    {27, 0x0000008b},
    {28, 0x00000090},
    {29, 0x00000098},
    {30, 0x000000a0},
    {31, 0x000000a8}};

  if (mCameraPropertiesUpdateSet.isoSpeed.sent) {
    mCameraPropertiesUpdateSet.isoSpeed.value = valueMap[value];
  } else {
    mCameraPropertiesUpdateSet.isoSpeed.sent = true;
    mCameraPropertiesUpdateSet.isoSpeed.value.reset();
    mConnectedCamera->setCameraProperty_isoSpeed(valueMap[value]);
  }
}
