// TODO: add define guard
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#define EXTENSION_NAME       "easyPlay"
#define EXTENSION_ID         "easyPlay@easyPlay"
#define MANIFEST_FILE_NAME   EXTENSION_NAME ".json"
#define MANIFEST_DESCRIPTION "EasyPlay Device Client"

// TODO: remove #Includes that are not needed

class ManifestHandler {
 public:
  static bool createManifest(const QString& directoryPath, const QString& clientExePath) {
    // TODO: add to cpp file
    // TODO: check that directory is real

    QString manifestPath = directoryPath + QDir::separator() + "easyPlay.json";  // TODO: use #define
    QFile manifestFile{manifestPath};

    if (!manifestFile.open(QFile::WriteOnly)) {
      // TODO: log
      return false;
    }

    QJsonObject manifestJson;
    manifestJson.insert("name", EXTENSION_NAME);
    manifestJson.insert("description", MANIFEST_DESCRIPTION);
    manifestJson.insert("path", QDir::cleanPath(clientExePath));
    manifestJson.insert("type", "stdio");
    manifestJson.insert("allowed_extensions", QJsonArray{{EXTENSION_ID}});

    QByteArray manifestContent = QJsonDocument{manifestJson}.toJson(QJsonDocument::Compact);

    if (manifestFile.write(manifestContent) < 0) {
      // TODO: log
      return false;
    }

    return true;
  }
};