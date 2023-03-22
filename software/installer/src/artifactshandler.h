#ifndef ARTIFACTSHANDLER_H
#define ARTIFACTSHANDLER_H

#include <QObject>
#include <QString>

#define DRIVER_EXE_FILE_NAME          "EasyPlay.exe"
#define NATIVE_APP_MANIFEST_FILE_NAME "easyplay-native-app-manifest.json"

class ArtifactsHandler : public QObject {
  Q_OBJECT
 public:
  explicit ArtifactsHandler(QObject* parent = nullptr);
  void copyAllArtifactsToDestDir(QString destDirAbsPath);

 private:
  bool copyToDestDir(QString destDirAbsPath, QString artifactFileName);
  QString getArtifactAbsPath(QString artifactFileName);
};

#endif  // ARTIFACTSHANDLER_H
