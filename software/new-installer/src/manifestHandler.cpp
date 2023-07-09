#include "manifestHandler.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

bool ManifestHandler::createManifest(const QString& directoryPath, const QString& clientExeAbsPath) {
  if (!QDir{directoryPath}.exists()) {
    qWarning("Manifest file directory doesn't exist");
    return false;
  }

  QString manifestPath = QDir::cleanPath(directoryPath + QDir::separator() + MANIFEST_FILE_NAME);
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
  manifestJson.insert("description", MANIFEST_DESCRIPTION);
  manifestJson.insert("path", QDir::cleanPath(clientExeAbsPath));
  manifestJson.insert("type", "stdio");
  manifestJson.insert("allowed_extensions", QJsonArray{{EXTENSION_ID}});

  QByteArray manifestContent = QJsonDocument{manifestJson}.toJson(QJsonDocument::Compact);

  if (manifestFile.write(manifestContent) < 0) {
    qWarning() << "Couldn't write to manifest file";
    return false;
  }

  return true;
}