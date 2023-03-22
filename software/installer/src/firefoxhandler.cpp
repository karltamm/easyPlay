#include "firefoxhandler.h"

#include <QDebug>

FirefoxHandler::FirefoxHandler(QObject* parent)
    : QObject{parent}, firefoxReg(new QSettings(FIREFOX_REG_PATH, QSettings::NativeFormat, this)) {
  qDebug() << "Path:" << getFirefoxPath();  // TODO: rm
}

FirefoxHandler::~FirefoxHandler() {
  firefoxReg->deleteLater();
}

bool FirefoxHandler::isFirefoxInstalled() {
  return firefoxReg->allKeys().length() > 0;
}

QString FirefoxHandler::getFirefoxPath() {
  foreach (QString key, firefoxReg->allKeys()) {
    if (!key.contains(FIREFOX_PATH_VALUE_NAME)) {
      continue;
    }
    return firefoxReg->value(key).toString();
  }
  return "";
}

// TODO: check if java is installed. if not, abort the installer and show message

// TODO: copy firefox extension to correct firefox folder

// TODO: when installing program, save installation path to registry value
// TODO: pass installation path to firefox handler, so it could add needed key/value to registry

// TODO: check if program is already installed when installing
// TODO: if program is already installed, then delete program folder based on the registry key
