#ifndef ARTIFACTSHANDLER_H
#define ARTIFACTSHANDLER_H

#include <copyhandler.h>
#include <QObject>
#include <QPointer>
#include <QSettings>
#include <QString>

#define DRIVER_EXE_FILE_NAME          "EasyPlay.exe"
#define NATIVE_APP_MANIFEST_FILE_NAME "easyplay-native-app-manifest.json"

#define EASYPLAY_ORG_REG_KEY       "EasyPlayOrg"
#define EASYPLAY_REG_KEY           "EasyPlay"
#define ARTIFACTS_DEST_DIR_REG_KEY "installationDirPath"

class ArtifactsHandler : public QObject {
  Q_OBJECT
 public:
  CopyHandler* copyHandler;

  explicit ArtifactsHandler(QObject* parent = nullptr);
  ~ArtifactsHandler();

 signals:
  void copyArtifacts(QString destDir);

 private:
  QSettings* appRegistry;
  QThread* copyThread;

  void setUpCopyHandler();
  void handleCopyRequest();
  void saveDestDirToReg(QString destDirPath);
};

#endif  // ARTIFACTSHANDLER_H
