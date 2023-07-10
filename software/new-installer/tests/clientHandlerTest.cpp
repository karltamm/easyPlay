#include <gtest/gtest.h>
#include <QDir>
#include <QFile>
#include <QFuture>

#include "clientHandler.h"

TEST(ClientHandlerTest, CanCopyClientFile) {
  QFuture<bool> copyResult = ClientHandler::copyClientFile(QDir::currentPath());
  //   copyResult.waitForFinished(); // TODO: rm
  EXPECT_TRUE(copyResult.result());  // TODO: add message
  //   EXPECT_TRUE(ClientHandler::copyClientFile(QDir::currentPath())); // TODO: rm                                      // TODO: add message
  EXPECT_TRUE(QFile::exists(QDir::currentPath() + "/easyplay-device-client")) << "File wasn't copied";  // TODO: use #define
}