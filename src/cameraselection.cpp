#include "cameraselection.hpp"

#undef max
#include <limits>

#include "ui_cameraselection.h"

#include "eos/deviceinfo.hpp"

CameraSelection::CameraSelection(QWidget *parent)
  : QDialog{parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint}
  , mUi{std::make_unique<Ui::CameraSelectionClass>()}
  , mSelectedCameraIndex{std::numeric_limits<std::size_t>::max()}
  , mDeviceList{} {
  mUi->setupUi(this);
}

CameraSelection::~CameraSelection() {
}

void CameraSelection::showEvent(QShowEvent *event) {
  refreshView();

  QDialog::showEvent(event);
}

std::size_t CameraSelection::getSelectedCameraIndex() {
  return mSelectedCameraIndex;
}

void CameraSelection::deviceListChanged(const std::vector<EOS::DeviceInfo>& deviceList) {
  if (mDeviceList == deviceList) {
    return;
  }

  mDeviceList = deviceList;

  if (isVisible()) {
    refreshView();
  }
}

void CameraSelection::refreshView() {
  mSelectedCameraIndex = std::numeric_limits<std::size_t>::max();
  mUi->okButton->setEnabled(false);

  mUi->camerasListWidget->clear();
  resetCamerasTableWidget();

  for (std::size_t i = 0; i < mDeviceList.size(); i ++) {
    mUi->camerasTableWidget->insertRow(i);
    mUi->camerasTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(mDeviceList[i].index)));
    mUi->camerasTableWidget->setItem(i, 1, new QTableWidgetItem(mDeviceList[i].description.c_str()));
    mUi->camerasTableWidget->setItem(i, 2, new QTableWidgetItem(mDeviceList[i].portName.c_str()));
    mUi->camerasTableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(mDeviceList[i].subtype)));
    mUi->camerasTableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(mDeviceList[i].reserved)));
  }

  mUi->camerasTableWidget->resizeColumnsToContents();
  mUi->camerasTableWidget->resizeRowsToContents();
}

void CameraSelection::resetCamerasTableWidget() {
  mUi->camerasTableWidget->clear();
  mUi->camerasTableWidget->setHorizontalHeaderLabels({"Index", "Description", "Port name", "Sub type", "Reserved"});
}
