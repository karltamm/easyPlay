// TODO: add guard
#include <QDir>
#include <QFile>
#include <QFuture>
#include <QString>
#include <QtConcurrent>

class ClientHandler {
 public:
  static QFuture<bool> copyClientFile(const QString& clientDestPath) {
    // TODO: add definition to cpp
    // TODO: add binary file to app as resource

    // TODO: use threads for copy
    // TODO: use future for output

    // QFile::copy("")

    return QtConcurrent::run([clientDestPath]() {
      QFile clientFile{":/easyplay-device-client"};

      // TODO: rm
      // qDebug() << "clientFile.size:" << clientFile.size();
      // qDebug() << "clientFile.exists:" << clientFile.exists();

      QDir{}.mkpath(clientDestPath);  // TODO: check for outcome

      clientFile.copy(clientDestPath + "/easyplay-device-client");  // TODO: use #define // TODO: check for outcome

      return true;
    });
  }
};