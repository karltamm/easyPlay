#include "artifactshandler.h"
#include <logger.h>
#include <QDir>
#include <QFile>

ArtifactsHandler::ArtifactsHandler(QObject* parent)
    : QObject{parent}, appRegistry(QSettings(APP_REG_KEY)) {
}

void ArtifactsHandler::copyAllArtifactsToDestDir(QString destDirAbsPath) {
  copyToDestDir(destDirAbsPath, DRIVER_EXE_FILE_NAME);
  copyToDestDir(destDirAbsPath, NATIVE_APP_MANIFEST_FILE_NAME);
}

bool ArtifactsHandler::copyToDestDir(QString destDirAbsPath, QString artifactFileName) {
  if (!QDir(destDirAbsPath).exists()) {
    qCritical() << "Artifacts destination folder doesn't exist:" << destDirAbsPath;
    return false;
  }
  QFile file(getArtifactAbsPath(artifactFileName));
  if (!file.exists()) {
    qCritical() << "Artifact doesn't exist:" << file.fileName();
    return false;
  }
  return file.copy(QDir::cleanPath(destDirAbsPath + QDir::separator() + artifactFileName));
}

QString ArtifactsHandler::getArtifactAbsPath(QString artifactFileName) {
  return QDir::cleanPath(QDir::currentPath() + QDir::separator() + artifactFileName);
}

bool ArtifactsHandler::prevInstallExists() {
  qDebug() << "applicationName:" << appRegistry.applicationName();       // TODO: rm
  qDebug() << "path:" << appRegistry.value(ARTIFACTS_DEST_DIR_REG_KEY);  // TODO: fix
  return false;                                                          // TODO: return path
}

// TODO: remove previous installation files after new files are installed

void ArtifactsHandler::removePrevInstallArtifacts() {}

void ArtifactsHandler::saveDestDirToReg(QString destDirAbsPath) {
  destDirAbsPath = QDir::cleanPath(destDirAbsPath);
  if (!QDir(destDirAbsPath).exists()) {
    // TODO: log warning
  }
  appRegistry.setValue(ARTIFACTS_DEST_DIR_REG_KEY, destDirAbsPath);
}
