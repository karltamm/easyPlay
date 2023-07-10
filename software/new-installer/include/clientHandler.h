// TODO: add guard
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFuture>
#include <QString>
#include <QtConcurrent>

#define CLIENT_FILE_NAME "easyplay-device-client"

class ClientHandler {
 public:
  static QFuture<bool> copyClientFile(const QString& clientDestDirPath) {
    // TODO: add definition to cpp

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
};