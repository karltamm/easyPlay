#include "artifactshandler.h"
#include <QDebug>
#include <QDir>
#include <QFile>

ArtifactsHandler::ArtifactsHandler(QObject* parent)
    : QObject{parent} {
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
