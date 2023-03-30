#include "artifactshandler.h"

#include <logger.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

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
    emit copyHandler->requestCopy({DRIVER_EXE_FILE_NAME}, destDir);
    createAppManifest(destDir);
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

void ArtifactsHandler::createAppManifest(QString destDirPath) {
  QJsonObject manifest;
  manifest.insert("name", "easyPlay");
  manifest.insert("description", "EasyPlay");
  manifest.insert("path", QDir::cleanPath(destDirPath + QDir::separator() + DRIVER_EXE_FILE_NAME));
  manifest.insert("type", "stdio");
  manifest.insert("allowed_extensions", QJsonArray({"easyPlay@easyPlay"}));

  QString filePath = QDir::cleanPath(destDirPath + QDir::separator() + NATIVE_APP_MANIFEST_FILE_NAME);
  QFile manifestFile(filePath);
  if (!manifestFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Couldn't open native app manifest file";
    return;
  }
  QString manifestText = QJsonDocument(manifest).toJson(QJsonDocument::Compact);
  if (manifestFile.write(manifestText.toUtf8()) < 0) {
    qWarning() << "Couldn't create native app manifest file:" << filePath;
  }
}
