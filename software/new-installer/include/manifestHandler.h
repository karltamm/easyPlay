// TODO: add define guard
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

// TODO: remove #Includes that are not needed

class ManifestHandler {
 public:
  static void createManifest(const QString& directoryPath, const QString& clientExePath) {
    // TODO: add to cpp file
    // TODO: check that directory is real

    QString manifestPath = directoryPath + QDir::separator() + "easyPlay.json";  // TODO: use #define
    QFile manifestFile{manifestPath};

    if (!manifestFile.open(QFile::WriteOnly)) {
      // TODO: log
      return;
    }

    QJsonObject manifestJson;
    manifestJson.insert("name", "easyPlay");  // TODO: use #define
    manifestJson.insert("description", "EasyPlay device client");
    manifestJson.insert("path", QDir::cleanPath(clientExePath));
    manifestJson.insert("type", "stdio");
    manifestJson.insert("allowed_extensions", QJsonArray({"easyPlay@easyPlay"}));  // TODO: use #define

    QByteArray manifestContent = QJsonDocument{manifestJson}.toJson(QJsonDocument::Compact);

    if (manifestFile.write(manifestContent) < 0) {
      // TODO: log
    }
  }
};