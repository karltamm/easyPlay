#include "firefoxHandler.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#define FIREFOX_PATH "/Applications/Firefox.app"

bool FirefoxHandler::isFirefoxInstalled() {
  return QDir{FIREFOX_PATH}.exists();
}

bool FirefoxHandler::createNativeManifest(const QString& directoryPath, const QString& clientExeAbsPath) {
  if (!QDir{directoryPath}.exists()) {
    qWarning("Manifest file directory doesn't exist");
    return false;
  }

  QString manifestPath = QDir::cleanPath(directoryPath + QDir::separator() + NATIVE_MANIFEST_FILE_NAME);  // TODO: use absoluteFilePath
  QFile manifestFile{manifestPath};

  if (!manifestFile.open(QFile::WriteOnly)) {
    qWarning("Couldn't create manifest file");
    return false;
  }

  if (!QDir::isAbsolutePath(clientExeAbsPath)) {
    qWarning() << "Client executable path is not absolute";
    return false;
  }

  QJsonObject manifestJson;
  manifestJson.insert("name", EXTENSION_NAME);
  manifestJson.insert("description", NATIVE_MANIFEST_DESCRIPTION);
  manifestJson.insert("path", QDir::cleanPath(clientExeAbsPath));
  manifestJson.insert("type", "stdio");
  manifestJson.insert("allowed_extensions", QJsonArray{{EXTENSION_ID}});

  QByteArray manifestContent = QJsonDocument{manifestJson}.toJson(QJsonDocument::Compact);  // TODO: inline

  if (manifestFile.write(manifestContent) < 0) {
    qWarning() << "Couldn't write to manifest file";
    return false;
  }

  return true;
}

QDir FirefoxHandler::getNativeAppManifestDir() {
  QString dirPath = QDir::homePath() + R"(/Library/Application Support/Mozilla/NativeMessagingHosts)";  // TODO: use #define

  QDir{}.mkpath(dirPath);  // TODO: use #define; // TODO: check for return

  return QDir{dirPath};
}