#include "clientHandler.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QtConcurrent>

#define REG_ORG_NAME        "easyPlay"
#define REG_APP_NAME        "easyPlay-installer"
#define REG_CLIENT_PATH_KEY "clientPath"

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

    const QString clientDestPath = clientDestDir.filePath(CLIENT_FILE_NAME);

    if (!clientFile.copy(clientDestPath) and !QFile::exists(clientDestPath)) {
      qWarning() << "Couldn't copy client file";
      return false;
    }

    ClientHandler::addClientDirPathToRegistry(clientDestDir.absolutePath());

    return true;
  });
}

bool ClientHandler::deleteExistingClientDir() {
  QString clientDirPath = ClientHandler::getClientDirPathFromRegistry();

  if (clientDirPath.isEmpty()) {
    qWarning() << "Can't delete existing client directory cause couldn't retrieve its path";
    return false;
  }

  if (!QDir{clientDirPath}.removeRecursively()) {
    qWarning() << "Couldn't remove client directory";
    return false;
  }

  return true;
}

QString ClientHandler::getClientDirPathFromRegistry() {
  QSettings installerRegistry{REG_ORG_NAME, REG_APP_NAME};                // TODO: use #define
  QVariant clientDirPath = installerRegistry.value(REG_CLIENT_PATH_KEY);  // TODO: rename

  return clientDirPath.isNull() ? "" : clientDirPath.toString();
}

void ClientHandler::addClientDirPathToRegistry(const QString& clientDirPath) {
  QSettings{REG_ORG_NAME, REG_APP_NAME}.setValue("clientPath", clientDirPath);  // TODO: use #define
}

bool ClientHandler::doesClientDirExist() {
  return !ClientHandler::getClientDirPathFromRegistry().isEmpty();
}