#include "clientHandler.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QSettings>
#include <QStringList>
#include <QtConcurrent>

#define REG_ORG_NAME            "easyPlay"
#define REG_APP_NAME            "easyPlay-installer"
#define REG_CLIENT_DIR_PATH_KEY "clientDirPath"

QFuture<QPair<bool, QString>> ClientHandler::copyClientFile(const QString& clientDestDirPath) {
  return QtConcurrent::run([clientDestDirPath]() -> QPair<bool, QString> {
    QFile clientFile{":/" CLIENT_FILE_NAME};

    if (!clientFile.exists()) {
      qWarning() << "Device client file doesn't exist";
      return {false, ""};
    }

    QDir clientDestDir{clientDestDirPath};

    if (!clientDestDir.exists()) {
      qWarning() << "Destination directory doesn't exist";
      return {false, ""};
    }

    const QString clientDestPath = clientDestDir.absoluteFilePath(CLIENT_FILE_NAME);

    if (!clientFile.copy(clientDestPath) and !QFile::exists(clientDestPath)) {
      qWarning() << "Couldn't copy client file";
      return {false, ""};
    }

    ClientHandler::makeFileExecutable(clientDestPath);
    ClientHandler::addClientDirPathToRegistry(clientDestDir.absolutePath());

    return {true, clientDestPath};
  });
}

bool ClientHandler::deleteExistingClientDir() {
  QDir clientDir = ClientHandler::getExistingClientDir();

  if (!clientDir.exists()) {
    qWarning() << "Can't delete existing client directory cause couldn't retrieve its path";
    return false;
  }

  if (!clientDir.removeRecursively()) {
    qWarning() << "Couldn't remove client directory";
    return false;
  }

  return true;
}

QDir ClientHandler::getExistingClientDir() {
  QVariant clientDirPath = QSettings{REG_ORG_NAME, REG_APP_NAME}.value(REG_CLIENT_DIR_PATH_KEY);

  if (clientDirPath.isNull()) {
    return QString{};
  }

  return QDir{clientDirPath.toString()};
}

void ClientHandler::addClientDirPathToRegistry(const QString& clientDirPath) {
  QSettings{REG_ORG_NAME, REG_APP_NAME}.setValue(REG_CLIENT_DIR_PATH_KEY, clientDirPath);
}

void ClientHandler::makeFileExecutable(const QString& filePath) {
  QProcess chmod;
  chmod.start("chmod", {"+x", filePath});
  chmod.waitForFinished();
}