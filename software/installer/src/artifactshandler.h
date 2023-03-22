#ifndef ARTIFACTSHANDLER_H
#define ARTIFACTSHANDLER_H

#include <QObject>

#define DRIVER_PATH "./assets/EasyPlay.exe"

class ArtifactsHandler : public QObject {
  Q_OBJECT
 public:
  explicit ArtifactsHandler(QObject* parent = nullptr);

 signals:
};

// TODO: rename to artifactsHandler
// TODO: change build directory and add this to gitignore

#endif  // ARTIFACTSHANDLER_H
