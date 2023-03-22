#include "firefoxhandler.h"

#include <logger.h>
#include <QFile>

FirefoxHandler::FirefoxHandler(QObject* parent)
    : QObject{parent}, mozillaRegistry(new QSettings(MOZILLA_REGISTRY_KEY, QSettings::NativeFormat, this)) {
}

FirefoxHandler::~FirefoxHandler() {
  mozillaRegistry->deleteLater();
}

bool FirefoxHandler::isFirefoxInstalled() {
  return QSettings(FIREFOX_REGISTRY_KEY, QSettings::NativeFormat).allKeys().length() > 0;
}

void FirefoxHandler::addNativeAppManifest(QString manifestAbsPath) {
  if (!QFile::exists("manifestAbsPath")) {
    qWarning() << "Native app manifest file doesn't exists:" << manifestAbsPath;
  }
  mozillaRegistry->setValue(EASYPLAY_NATIVE_APP_KEY_NAME, manifestAbsPath);
}
