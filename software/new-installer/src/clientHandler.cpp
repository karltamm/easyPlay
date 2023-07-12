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
    qWarning() << "Can't delete existing client cause couldn't retrieve its path";
    return false;
  }

  if (!QFile{clientPath}.remove()) {
    qWarning() << "Couldn't remove client file";
    return false;
  }

  return true;
}

QString ClientHandler::getClientPathFromRegistry() {
  QSettings installerRegistry{REG_ORG_NAME, REG_APP_NAME};
  QVariant clientPath = installerRegistry.value(REG_CLIENT_PATH_KEY);

  return clientPath.isNull() ? "" : clientPath.toString();
}

void ClientHandler::addClientPathToRegistry(const QString& clientAbsPath) {
  QSettings{REG_ORG_NAME, REG_APP_NAME}.setValue("clientPath", clientAbsPath);
}

bool ClientHandler::doesClientFileExist() {
  return !ClientHandler::getClientPathFromRegistry().isEmpty();
}