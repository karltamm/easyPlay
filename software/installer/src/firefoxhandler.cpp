#include "firefoxhandler.h"

#include <QDebug>

FirefoxHandler::FirefoxHandler(QObject* parent)
    : QObject{parent}, mozillaRegistry(new QSettings(MOZILLA_REGISTRY_KEY, QSettings::NativeFormat, this)) {
  addNativeAppManifest("abc");  // TODO: rm
}

FirefoxHandler::~FirefoxHandler() {
  mozillaRegistry->deleteLater();
}

bool FirefoxHandler::isFirefoxInstalled() {
  return QSettings(FIREFOX_REGISTRY_KEY, QSettings::NativeFormat).allKeys().length() > 0;
}

void FirefoxHandler::addNativeAppManifest(QString manifestAbsPath) {
  // Manifest file (JSON) must be already installed to the computer, when call this method
  // TODO: check if file exists.
  mozillaRegistry->setValue(EASYPLAY_NATIVE_APP_KEY_NAME, manifestAbsPath);
}

// TODO: check if java is installed. if not, abort the installer and show message
// TODO: when installing program, save installation path to registry value
// TODO: pass installation path to firefox handler, so it could add needed key/value to registry
// TODO: check if program is already installed when installing
// TODO: if program is already installed, then delete program folder based on the registry key
