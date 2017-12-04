#pragma once

#include <string>
#include <memory>

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <edsdk/EDSDK.h>
#include <edsdk/EDSDKTypes.h>
#include <edsdk/EDSDKErrors.h>

#include "cameralist.hpp"

namespace EOS {
  class CameraController : public QObject {
    Q_OBJECT

  public:
    CameraController(QObject *parent = Q_NULLPTR);
    ~CameraController();
    bool isInitialized();
    bool startCameraListChangeListener();
    static std::string getErrorDescription();

  private:
    QTimer mCameraListTimer;
    std::shared_ptr<CameraList> mCameraList;

    EdsError CameraAddedHandler();
    static EdsError EDSCALLBACK CameraAddedHandlerCallback(EdsVoid *inContext);
    bool mSdkInitialized;

  signals:
    void camerasListChanged(const std::vector<CameraInfo> &camerasList);

  public slots:
    void updateCameraList();
  };
}
