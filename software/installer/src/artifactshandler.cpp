#include "artifactshandler.h"

#include <logger.h>
#include <QFile>
#include <QtConcurrent/QtConcurrent>  // TODO: rm

ArtifactsHandler::ArtifactsHandler(QObject* parent)
    : QObject{parent},
      copyHandler{new CopyHandler()},  // Without parent to allow moveToThread
      appRegistry{new QSettings(EASYPLAY_ORG_REG_KEY, EASYPLAY_REG_KEY, this)},
      copyThread{new QThread(this)} {
  setUpCopyHandler();
  handleCopyRequest();
}

ArtifactsHandler::~ArtifactsHandler() {
  copyHandler->deleteLater();
  copyThread->quit();
  QThread::msleep(100);  // Necessary that copyThread can exit without problems
}

QDir ArtifactsHandler::getPreviousInstallationDir() {
  return QDir(appRegistry->value(ARTIFACTS_DEST_DIR_REG_KEY).toString());
}

bool ArtifactsHandler::deletePreviousInstallation() {
  QDir prevDir = getPreviousInstallationDir();
  if (!prevDir.exists()) {
    return false;
  }
  return prevDir.removeRecursively();
}

void ArtifactsHandler::setUpCopyHandler() {
  if (copyThread->isRunning()) {
    qWarning() << "Copy handler is already set up";
    return;
  }
  copyHandler->moveToThread(copyThread);
  connect(copyThread, &QThread::started, copyHandler, &CopyHandler::run);
  copyThread->start();
}

void ArtifactsHandler::handleCopyRequest() {
  connect(this, &ArtifactsHandler::copyArtifacts, this, [this](QString destDir) {
    emit copyHandler->requestCopy({DRIVER_EXE_FILE_NAME, NATIVE_APP_MANIFEST_FILE_NAME}, destDir);
    saveDestDirToReg(destDir);
  });
}

void ArtifactsHandler::saveDestDirToReg(QString destDirPath) {
  destDirPath = QDir::cleanPath(destDirPath);
  if (!QDir(destDirPath).exists()) {
    qWarning() << "Destination directory doesn't exist";
  }
  appRegistry->setValue(ARTIFACTS_DEST_DIR_REG_KEY, destDirPath);
}
