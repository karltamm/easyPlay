#ifndef ARTIFACTSHANDLER_H
#define ARTIFACTSHANDLER_H

#include <QObject>
#include <QSettings>
#include <QString>

#define DRIVER_EXE_FILE_NAME          "EasyPlay.exe"
#define NATIVE_APP_MANIFEST_FILE_NAME "easyplay-native-app-manifest.json"

#define APP_REG_KEY                "EasyPlay"
#define ARTIFACTS_DEST_DIR_REG_KEY "installationDirPath"

class ArtifactsHandler : public QObject {
  Q_OBJECT
 public:
  explicit ArtifactsHandler(QObject* parent = nullptr);

  void copyAllArtifactsToDestDir(QString destDirAbsPath);

  // TODO Karl: use signal installPathSelected to
  // (1) check if prevInstallExists
  // (2) removePrevInstallArtifacts() (if user wants it)
  // (3) saveDestDirToReg

 signals:
  void prevInstallExists(QString installDirPath);

 private:
  QSettings appRegistry;  // TODO: make it pointer

  bool copyToDestDir(QString destDirAbsPath, QString artifactFileName);
  QString getArtifactAbsPath(QString artifactFileName);
  bool prevInstallExists();
  void removePrevInstallArtifacts();
  void saveDestDirToReg(QString destDirAbsPath);
};

#endif  // ARTIFACTSHANDLER_H
