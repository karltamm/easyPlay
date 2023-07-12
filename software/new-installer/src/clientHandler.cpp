#include "clientHandler.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QtConcurrent>

QFuture<bool> ClientHandler::copyClientFile(const QString& clientDestDirPath) {
  return QtConcurrent::run([clientDestDirPath]() {
    QFile clientFile{":/" CLIENT_FILE_NAME};

    if (!clientFile.exists()) {
      qWarning() << "Device client file doesn't exist";
      return false;
    }

    QDir clientDestDir{clientDestDirPath};

    if (!clientDestDir.mkpath(clientDestDirPath)) {
      qWarning() << "Couldn't create directory for client file";
      return false;
    }

    const QString clientDestPath = clientDestDir.absoluteFilePath(CLIENT_FILE_NAME);

    if (!clientFile.copy(clientDestPath) and !QFile::exists(clientDestPath)) {
      qWarning() << "Couldn't copy client file";
      return false;
    }

    ClientHandler::addClientPathToRegistry(clientDestPath);

    return true;
  });
}

bool ClientHandler::deleteExistingClientFile() {
  QString clientPath = ClientHandler::getClientPathFromRegistry();

  if (clientPath.isEmpty()) {
    // TODO: log
    return false;
  }

  return QFile{clientPath}.remove();  // TODO: check return false
}

QString ClientHandler::getClientPathFromRegistry() {
  QSettings installerRegistry{"easyplay", "easyplay-installer"};  // TODO: use #define
  QVariant clientPath = installerRegistry.value("clientPath");    // TODO: use #define

  return clientPath.isNull() ? "" : clientPath.toString();  // TODO: rm
}

void ClientHandler::addClientPathToRegistry(const QString& clientAbsPath) {
  QSettings{"easyplay", "easyplay-installer"}.setValue("clientPath", clientAbsPath);  // TODO: use #define
}

// TODO: create addClientPathToRegistry()

bool ClientHandler::doesClientFileExist() {
}