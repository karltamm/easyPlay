#ifndef MANIFEST_HANDLER_H
#define MANIFEST_HANDLER_H

#include <QString>

#define EXTENSION_NAME       "easyPlay"
#define EXTENSION_ID         "easyPlay@easyPlay"
#define MANIFEST_FILE_NAME   EXTENSION_NAME ".json"
#define MANIFEST_DESCRIPTION "EasyPlay Device Client"

class ManifestHandler {
 public:
  static bool createManifest(const QString& directoryPath, const QString& clientExePath);
};

#endif  // MANIFEST_HANDLER_H