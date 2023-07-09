#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include <gtest/gtest.h>
#include <QChar>
#include <QFile>
#include <QString>

#include "manifestHandler.h"

// TODO: create test class

// #define MANIFEST_ABS_PATH R"(/Users/karl/Library/Application Support/Mozilla/NativeMessagingHosts/easyPlay.json)"

TEST(ManifestHandlerTest, CanCreateManifestFile) {
  // TODO: get home path and don't use abs path
  std::ifstream manifestFile{"easyPlay.json"};                             // TODO: use #define
  ManifestHandler::createManifest(QDir::currentPath(), "directory/file");  // TODO: use #define

  // TODO: use build folder path for the file

  // TODO: check that file can be opened (exists)

  // TODO: use path set above
  // std::string expectedContent = {"{\"name\":\"easyPlay\",\"description\":\"EasyPlaydeviceclient\",\"path\":\"directory/file\",\"type\":\"stdio\",\"allowed_extensions\":[\"easyPlay@easyPlay\"]}"};  // TODO: use #define // TODO: remove

  // TODO: use sstream
  QString expectedContent = QObject::tr("{\"allowed_extensions\":[\"%1\"],\"description\":\"%2\",\"name\":\"%3\",\"path\":\"%4\",\"type\":\"stdio\"}").arg("easyPlay@easyPlay", "EasyPlaydeviceclient", "easyPlay", "directory/file");  // TODO: use #define

  // TODO: rm
  // auto manifestFile = QFile{"easyPlay.json"};
  // if (!manifestFile.open(QFile::ReadOnly)) {
  //   // TODO: log
  //   return;
  // }

  // auto realContent = QString{manifestFile.readAll()};

  // realContent.removeIf
  // TODO; rm
  // EXPECT_TRUE(expectedContent.compare(realContent) == 0) << "Real content:" << realContent.toStdString() << std::endl
  //                                                        << "Expected: " << expectedContent.toStdString();

  // EXPECT_STREQ(expectedContent.constData(), realContent.constData()); // TODO: rm

  std::string realContent{std::istreambuf_iterator<char>(manifestFile), std::istreambuf_iterator<char>()};
  realContent.erase(std::remove_if(realContent.begin(), realContent.end(), isspace), realContent.end());  // TODO: rm

  EXPECT_TRUE(expectedContent.compare(QString::fromStdString(realContent)) == 0) << "Real content:" << realContent << std::endl
                                                                                 << "Expected: " << expectedContent.toStdString();
}