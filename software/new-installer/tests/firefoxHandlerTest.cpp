
#include <gtest/gtest.h>
#include <QDir>
#include <QFile>
#include <QString>

#include "firefoxHandler.h"

#define CLIENT_EXE_PATH "/directory/file"

TEST(FirefoxHandlerTest, FirefoxIsInstalled) {
  EXPECT_TRUE(FirefoxHandler::isFirefoxInstalled());
}

TEST(FirefoxHandlerTest, CanCreateManifestFile) {
  ASSERT_TRUE(FirefoxHandler::createNativeAppManifest(QDir::currentPath(), CLIENT_EXE_PATH)) << "Manifest creation failed";

  auto manifestFile = QFile{NATIVE_MANIFEST_FILE_NAME};
  ASSERT_TRUE(manifestFile.open(QFile::ReadOnly)) << "Couldn't open the manifest file";

  auto realContent = QString{manifestFile.readAll()};
  auto expectedContent = QObject::tr(R"({"allowed_extensions":["%1"],"description":"%2","name":"%3","path":"%4","type":"stdio"})")
                             .arg(EXTENSION_ID,
                                  NATIVE_MANIFEST_DESCRIPTION,
                                  EXTENSION_NAME,
                                  CLIENT_EXE_PATH);

  ASSERT_TRUE(expectedContent.compare(realContent) == 0) << "Real content:" << realContent.toStdString() << std::endl
                                                         << "Expected: " << expectedContent.toStdString();
}