#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <QDir>
#include <QFuture>
#include <QPair>
#include <QString>

#define CLIENT_FILE_NAME "easyplay-device-client"  // TODO: rename

class ClientHandler {
 public:
  static QFuture<QPair<bool, QString>> copyClientFile(const QString& clientDestDirPath);
  static bool deleteExistingClientDir();
  static QDir getExistingClientDir();

 private:
  static void addClientDirPathToRegistry(const QString& clientDir);
};

#endif  // CLIENT_HANDLER_H