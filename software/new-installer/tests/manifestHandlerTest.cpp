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

#define CLIENT_EXE_PATH "directory/file"

TEST(ManifestHandlerTest, CanCreateManifestFile) {
  ManifestHandler::createManifest(QDir::currentPath(), CLIENT_EXE_PATH);

  auto manifestFile = QFile{MANIFEST_FILE_NAME};
  EXPECT_TRUE(manifestFile.open(QFile::ReadOnly)) << "Couldn't open the manifest file";

  auto realContent = QString{manifestFile.readAll()};
  auto expectedContent = QObject::tr(R"({"allowed_extensions":["%1"],"description":"%2","name":"%3","path":"%4","type":"stdio"})")
                             .arg(EXTENSION_ID,
                                  MANIFEST_DESCRIPTION,
                                  EXTENSION_NAME,
                                  CLIENT_EXE_PATH);

  EXPECT_TRUE(expectedContent.compare(realContent) == 0) << "Real content:" << realContent.toStdString() << std::endl
                                                         << "Expected: " << expectedContent.toStdString();
}