#include "artifactshandler.h"

#include <logger.h>
#include <QDir>
#include <QFile>
#include <QtConcurrent/QtConcurrent>

ArtifactsHandler::ArtifactsHandler(QObject* parent)
    : QObject{parent},
      copyHandler{new CopyHandler()},
      appRegistry{new QSettings(APP_REG_KEY, QString(), this)},
      copyThread{new QThread(this)} {
  setUpCopyHandler();
}

ArtifactsHandler::~ArtifactsHandler() {
  copyHandler->deleteLater();
  copyThread->quit();
  QThread::msleep(100);  // Necessary that copyThread can exit without problems
}

void ArtifactsHandler::setUpCopyHandler() {
  if (copyThread->isRunning()) {
    // TODO: log
    return;
  }
  copyHandler->moveToThread(copyThread);
  connect(copyThread, &QThread::started, copyHandler, &CopyHandler::run);
  copyThread->start();
}

void ArtifactsHandler::saveDestDirToReg(QString destDirPath) {
  destDirPath = QDir::cleanPath(destDirPath);
  if (!QDir(destDirPath).exists()) {
    // TODO: log warning
  }
  appRegistry->setValue(ARTIFACTS_DEST_DIR_REG_KEY, destDirPath);
}
