#include "cameraselection.hpp"

#undef max
#include <limits>

#include "ui_cameraselection.h"

#include "eos/camerainfo.hpp"
#include "eos/sdk.hpp"

CameraSelection::CameraSelection(const std::shared_ptr<EOS::SDK> &sdk, QWidget *parent)
  : QDialog{parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint}
  , mUi{std::make_unique<Ui::CameraSelectionClass>()}
  , mSDK{sdk}
  , mCameraList{} {
  mUi->setupUi(this);

  mSDK->registerCameraListChangedListener(this);
}

CameraSelection::~CameraSelection() {
  mSDK->unregisterCameraListChangedListener(this);
}

std::size_t CameraSelection::getSelectedCameraIndex() const {
  if (!mUi->camerasListWidget->currentItem() || !mUi->camerasListWidget->currentItem()->isSelected()) {
    return kInvalidIndex;
  }
  
  return mUi->camerasListWidget->currentItem()->data(Qt::UserRole).toUInt();
}

void CameraSelection::showEvent(QShowEvent *event) {
  refreshView();

  QDialog::showEvent(event);
}

void CameraSelection::cameraListChanged(const std::vector<EOS::CameraInfo>& cameraList) {
  if (mCameraList == cameraList) {
    return;
  }

  mCameraList = cameraList;

  if (isVisible()) {
    refreshView();
  }
}

void CameraSelection::refreshView() {
  mUi->camerasListWidget->clear();

  for (const auto &cameraInfo : mCameraList) {
    QListWidgetItem *item = new QListWidgetItem{cameraInfo.description.c_str(), mUi->camerasListWidget};
    item->setData(Qt::UserRole, QVariant{cameraInfo.index});
  }

  itemSelectionChanged();
}

void CameraSelection::itemSelectionChanged() {
  if (!mUi->camerasListWidget->currentItem() || !mUi->camerasListWidget->currentItem()->isSelected()) {
    mUi->okButton->setEnabled(false);
    mUi->okButton->clearFocus();
    mUi->indexDataLabel->setText("");
    mUi->portNameDataLabel->setText("");
    mUi->descriptionDataLabel->setText("");
    mUi->subtypeDataLabel->setText("");
    mUi->reservedDataLabel->setText("");
    return;
  }
  mUi->okButton->setEnabled(true);
  mUi->okButton->setFocus();
  std::size_t index = getSelectedCameraIndex();
  mUi->indexDataLabel->setText(QString::number(mCameraList[index].index));
  mUi->portNameDataLabel->setText(mCameraList[index].portName.c_str());
  mUi->descriptionDataLabel->setText(mCameraList[index].description.c_str());
  mUi->subtypeDataLabel->setText(QString::number(mCameraList[index].subtype));
  mUi->reservedDataLabel->setText(QString::number(mCameraList[index].reserved));
}

void CameraSelection::itemDoubleClicked() {
  if (mUi->camerasListWidget->currentItem() && mUi->camerasListWidget->currentItem()->isSelected()) {
    accept();
  }
}

const std::size_t CameraSelection::kInvalidIndex{std::numeric_limits<std::size_t>::max()};
