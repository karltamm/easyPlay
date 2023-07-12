#include <gtest/gtest.h>
#include <QDir>
#include <QFile>
#include <QFuture>

#include "clientHandler.h"

void copyClientFile() {
  QFile::remove(CLIENT_FILE_NAME);
  QFuture<bool> copyResult = ClientHandler::copyClientFile(QDir::currentPath());

  EXPECT_TRUE(copyResult.result()) << "ClientHandler::copyClientFile failed";
}

TEST(ClientHandlerTest, CanCopyClientFile) {
  copyClientFile();
  EXPECT_TRUE(QFile::exists(CLIENT_FILE_NAME)) << "File wasn't copied";
}

TEST(ClientHandlerTest, CanDeleteExistingClientFile) {
  copyClientFile();
  EXPECT_TRUE(ClientHandler::deleteExistingClientFile());

  EXPECT_FALSE(QFile::exists(CLIENT_FILE_NAME));
}