#include <gtest/gtest.h>
#include <QDir>
#include <QFile>
#include <QFuture>

#include "clientHandler.h"

#define CLIENT_DIR_PATH QDir::currentPath() + "/tempClientDir/"
#define CLIENT_PATH     CLIENT_DIR_PATH + CLIENT_FILE_NAME

void copyClientFile() {
  EXPECT_TRUE(QDir{CLIENT_DIR_PATH}.removeRecursively());
  EXPECT_TRUE(QDir{}.mkpath(CLIENT_DIR_PATH)) << "Couldn't create directory for client file";

  QFuture<QPair<bool, QString>> copyResult = ClientHandler::copyClientFile(CLIENT_DIR_PATH);
  EXPECT_TRUE(copyResult.result().first) << "ClientHandler::copyClientFile failed";
}

TEST(ClientHandlerTest, CanCopyClientFile) {
  copyClientFile();
  EXPECT_TRUE(QFile::exists(CLIENT_PATH)) << "File wasn't copied";
}

TEST(ClientHandlerTest, CanDeleteExistingClientDir) {
  copyClientFile();
  EXPECT_TRUE(ClientHandler::deleteExistingClientDir());
  EXPECT_FALSE(QFile::exists(CLIENT_PATH));
}