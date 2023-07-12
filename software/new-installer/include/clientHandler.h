#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <QFuture>
#include <QString>

#define CLIENT_FILE_NAME "easyplay-device-client"

class ClientHandler {
 public:
  static QFuture<bool> copyClientFile(const QString& clientDestDirPath);
  static bool deleteExistingClientFile();
  static bool doesClientFileExist();
};

#endif  // CLIENT_HANDLER_H