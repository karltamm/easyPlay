#include <gtest/gtest.h>
#include <QDir>
#include <QFile>
#include <QFuture>

#include "clientHandler.h"

TEST(ClientHandlerTest, CanCopyClientFile) {
  const QString clientFilePath = CLIENT_FILE_NAME;

  QFile::remove(clientFilePath);
  QFuture<bool> copyResult = ClientHandler::copyClientFile(QDir::currentPath());

  EXPECT_TRUE(copyResult.result()) << "ClientHandler::copyClientFile failed";
  EXPECT_TRUE(QFile::exists(clientFilePath)) << "File wasn't copied";
}