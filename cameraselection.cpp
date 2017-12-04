#include "cameraselection.hpp"

#undef max
#include <limits>

CameraSelection::CameraSelection(QWidget *parent)
  : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint)
  , mSelectedCameraIndex{std::numeric_limits<EdsUInt32>::max()} {
  ui.setupUi(this);

  resetCamerasTableWidget();
  ui.camerasTableWidget->resizeColumnsToContents();
  ui.camerasTableWidget->resizeRowsToContents();
}

void CameraSelection::showEvent(QShowEvent *event) {
  /*for (auto *item : ui.camerasTableWidget->selectedItems()) {
    item->setSelected(false);
  }
  ui.okButton->setEnabled(false);*/
}

void CameraSelection::camerasListUpdate(const std::vector<EOS::CameraInfo> &camerasList) {
  std::vector<EOS::CameraInfo> cameraList2;
  cameraList2.push_back({0, "dsasdsa", "ewqeqweqweqw", 2, 321});
  cameraList2.push_back({1, "dsasdsa323", "ewqeqweqwe21121qw", 3, 32441});
  cameraList2.push_back({2, "dsasdsa333", "ewqeqweqw44421eqw", 4, 32551});
  resetCamerasTableWidget();
  for (std::size_t i = 0; i < cameraList2.size(); i ++) {
    ui.camerasTableWidget->insertRow(i);
    ui.camerasTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(cameraList2[i].index)));
    ui.camerasTableWidget->setItem(i, 1, new QTableWidgetItem(cameraList2[i].description.c_str()));
    ui.camerasTableWidget->setItem(i, 2, new QTableWidgetItem(cameraList2[i].portName.c_str()));
    ui.camerasTableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(cameraList2[i].subType)));
    ui.camerasTableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(cameraList2[i].reserved)));
  }
  ui.camerasTableWidget->resizeColumnsToContents();
  ui.camerasTableWidget->resizeRowsToContents();
}

EdsUInt32 CameraSelection::getSelectedCameraIndex() {
  return mSelectedCameraIndex;
}

void CameraSelection::resetCamerasTableWidget() {
  ui.camerasTableWidget->clear();
  ui.camerasTableWidget->setHorizontalHeaderLabels({"Index", "Description", "Port name", "Sub type", "Reserved"});
}
