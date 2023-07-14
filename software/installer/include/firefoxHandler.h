#ifndef FIREFOX_HANDLER_H
#define FIREFOX_HANDLER_H

#include <QDir>
#include <QString>

#define EXTENSION_NAME              "easyPlay"
#define EXTENSION_ID                "easyPlay@easyPlay"
#define NATIVE_MANIFEST_FILE_NAME   EXTENSION_NAME ".json"
#define NATIVE_MANIFEST_DESCRIPTION "EasyPlay Device Client"

class FirefoxHandler {
 public:
  static bool isFirefoxInstalled();
  static bool createNativeAppManifest(const QString& manifestDirPath, const QString& appAbsPath);
  static QDir getNativeAppManifestDir();
};

#endif  // FIREFOX_HANDLER_H