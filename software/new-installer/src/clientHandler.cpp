#include "clientHandler.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QtConcurrent>

QFuture<bool> ClientHandler::copyClientFile(const QString& clientDestDirPath) {
  return QtConcurrent::run([clientDestDirPath]() {
    QFile clientFile{":/" CLIENT_FILE_NAME};

    if (!clientFile.exists()) {
      qWarning() << "Device client file doesn't exist";
      return false;
    }

    if (!QDir{}.mkpath(clientDestDirPath)) {
      qWarning() << "Couldn't create directory for client file";
      return false;
    }

    const QString clientDestPath = clientDestDirPath + QDir::separator() + CLIENT_FILE_NAME;

    if (!clientFile.copy(clientDestPath) and !QFile::exists(clientDestPath)) {
      qWarning() << "Couldn't copy client file";
      return false;
    }

    return true;
  });
}

bool ClientHandler::deleteExistingClientFile() {
}

bool ClientHandler::doesClientFileExist() {
}