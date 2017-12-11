#pragma once

#include <memory>
#include <vector>

#include <QtWidgets/QDialog>

#include "eos/cameralistchangedlistener.hpp"

namespace Ui {
  class CameraSelectionClass;
}

namespace EOS {
  class SDK;
  class CameraInfo;
}

class CameraSelection : public QDialog
                      , public EOS::CameraListChangedListener {
  Q_OBJECT

public:
  CameraSelection(const std::shared_ptr<EOS::SDK> &sdk, QWidget *parent = nullptr);
  ~CameraSelection() override;
  std::size_t getSelectedCameraIndex() const;

public:
  static const std::size_t kInvalidIndex;

public: // QDialog
  void showEvent(QShowEvent *event) override;

public: // EOS::CameraListChangedListener
  void cameraListChanged(const std::vector<EOS::CameraInfo> &cameraList) override;

private:
  const std::unique_ptr<Ui::CameraSelectionClass> mUi;
  std::shared_ptr<EOS::SDK> mSDK;
  std::vector<EOS::CameraInfo> mCameraList;

  void refreshView();

public slots:
  void itemSelectionChanged();
  void itemDoubleClicked();
};
