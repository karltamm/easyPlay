#include "firefoxHandler.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#define FIREFOX_PATH                 "/Applications/Firefox.app"
#define NATIVE_APP_MANIFEST_DIR_PATH R"(/Library/Application Support/Mozilla/NativeMessagingHosts)"

bool FirefoxHandler::isFirefoxInstalled() {
  return QDir{FIREFOX_PATH}.exists();
}

bool FirefoxHandler::createNativeAppManifest(const QString& manifestDirPath, const QString& appAbsPath) {
  QDir manifestDir{manifestDirPath};

  if (!manifestDir.exists()) {
    qWarning("Manifest file directory doesn't exist");
    return false;
  }

  QString manifestPath = manifestDir.absoluteFilePath(NATIVE_MANIFEST_FILE_NAME);
  QFile manifestFile{manifestPath};

  if (!manifestFile.open(QFile::WriteOnly)) {
    qWarning("Couldn't create manifest file");
    return false;
  }

  if (!QDir::isAbsolutePath(appAbsPath)) {
    qWarning() << "Client executable path is not absolute";
    return false;
  }

  QJsonObject manifestJson;
  manifestJson.insert("name", EXTENSION_NAME);
  manifestJson.insert("description", NATIVE_MANIFEST_DESCRIPTION);
  manifestJson.insert("path", QDir::cleanPath(appAbsPath));
  manifestJson.insert("type", "stdio");
  manifestJson.insert("allowed_extensions", QJsonArray{{EXTENSION_ID}});

  if (manifestFile.write(QJsonDocument{manifestJson}.toJson(QJsonDocument::Compact)) < 0) {
    qWarning() << "Couldn't write to manifest file";
    return false;
  }

  return true;
}

QDir FirefoxHandler::getNativeAppManifestDir() {
  QString dirPath = QDir::homePath() + NATIVE_APP_MANIFEST_DIR_PATH;

  if (!QDir{}.mkpath(dirPath)) {
    qWarning() << "Firefox native app manifest directory doesn't exist";
  }

  return QDir{dirPath};
}