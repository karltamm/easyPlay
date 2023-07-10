#include <gtest/gtest.h>
#include <QDir>
#include <QFile>

#include "clientHandler.h"

TEST(ClientHandlerTest, CanCopyClientFile) {
  EXPECT_TRUE(ClientHandler::copyClientFile(QDir::currentPath()));                                      // TODO: add message
  EXPECT_TRUE(QFile::exists(QDir::currentPath() + "/easyplay-device-client")) << "File wasn't copied";  // TODO: use #define
}