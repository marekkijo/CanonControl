#include "canoncontrol.hpp"

#include <QtWidgets/QMessageBox>

CanonControl::CanonControl(QWidget *parent)
  : QMainWindow(parent)
  , mCameraSelection(this)
  , mCameraController(this) {
  ui.setupUi(this);
  ui.statusBar->showMessage("Disconnected");
}

void CanonControl::showEvent(QShowEvent *event) {
  if (!mCameraController.isInitialized()) {
    QMessageBox::critical(this, QString("Critical error"), QString("Failed to initialize EDSDK: ") + QString(mCameraController.getErrorDescription().c_str()));
  } else {
    connect(&mCameraController, &EOS::CameraController::camerasListChanged,
            this, &CanonControl::camerasListUpdate);
    connect(&mCameraController, &EOS::CameraController::camerasListChanged,
            &mCameraSelection, &CameraSelection::camerasListUpdate);
    mCameraController.startCameraListChangeListener();
  }
  QMainWindow::showEvent(event);
}

void CanonControl::camerasListUpdate(const std::vector<EOS::CameraInfo>& camerasList) {
}

void CanonControl::connectionButtonClicked() {
  if (mCameraSelection.exec()) {
    QMessageBox::critical(this, QString("Critical error"), QString::number(mCameraSelection.getSelectedCameraIndex()));
  }
  
}
