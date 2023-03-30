#include "copyhandler.h"

#include <logger.h>
#include <QDir>

CopyHandler::CopyHandler(QObject* parent)
    : QObject{parent} {
}

void CopyHandler::run() {
  handleCopyRequest();
}

void CopyHandler::handleCopyRequest() {
  connect(this, &CopyHandler::requestCopy, this, [this](QStringList fileNames, QString destDirPath) {
    foreach (QString fileName, fileNames) {
      if (!copyFileToDir(fileName, destDirPath)) {
        emit copyResult(false);
        return;
      }
    }
    emit copyResult(true);
  });
}

bool CopyHandler::copyFileToDir(QString fileName, QString dirPath) {
  if (!QDir(dirPath).exists()) {
    qCritical() << "Destination folder doesn't exist:" << dirPath;
    return false;
  }
  QFile file(getFileAbsPath(fileName));
  if (!file.exists()) {
    qCritical() << "File doesn't exist:" << file.fileName();
    return false;
  }
  return file.copy(QDir::cleanPath(dirPath + QDir::separator() + fileName));
}

QString CopyHandler::getFileAbsPath(QString fileName) {
  return QDir::cleanPath(QDir::currentPath() + QDir::separator() + fileName);
}
