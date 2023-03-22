#include "firefoxhandler.h"

#include <QDebug>

FirefoxHandler::FirefoxHandler(QObject* parent)
    : QObject{parent}, firefoxReg(new QSettings(FIREFOX_KEY, QSettings::NativeFormat, this)) {
  addNativeAppManifest("abc");
}

FirefoxHandler::~FirefoxHandler() {
  firefoxReg->deleteLater();
}

bool FirefoxHandler::isFirefoxInstalled() {
  return firefoxReg->allKeys().length() > 0;
}

void FirefoxHandler::addNativeAppManifest(QString manifestAbsPath) {
  // Manifest file (JSON) must be already installed to the computer, when call this method
  // TODO: check if file exists.

  //  foreach (QString key, firefoxReg->allKeys()) {
  //    if (!key.contains("NativeMessagingHosts")) {
  //      continue;
  //    }
  //    qDebug() << "key:" << key;
  //  }

  //  qDebug() << "Contains:" << firefoxReg->contains(FIREFOX_NATIVE_MESSAGING_HOSTS_KEY);  // TODO: rm
  firefoxReg->setValue("NativeMessagingHosts/banana/.", "abc");  // TODO: fix
  //  qDebug() << "isWritable" << firefoxReg->isWritable();
  //  qDebug() << "addNativeAppManifest";  // TODO: rm

  // TODO: rm
  QSettings set("TestCompany", "TestProduct");
  set.setValue("my1Key", "myValue");
  set.setValue("my2Key/abc", "myValue");

  QSettings natReg(R"(HKEY_LOCAL_MACHINE\SOFTWARE\Mozilla\NativeMessagingHosts)", QSettings::NativeFormat);
  natReg.setValue("abc/dfg", "works");
}

// QString FirefoxHandler::getFirefoxPath() {
//   foreach (QString key, firefoxReg->allKeys()) {
//     if (!key.contains(FIREFOX_PATH_VALUE_NAME)) {
//       continue;
//     }
//     return firefoxReg->value(key).toString();
//   }
//   return "";
// }

// TODO: check if java is installed. if not, abort the installer and show message

// TODO: copy firefox extension to correct firefox folder

// TODO: when installing program, save installation path to registry value
// TODO: pass installation path to firefox handler, so it could add needed key/value to registry

// TODO: check if program is already installed when installing
// TODO: if program is already installed, then delete program folder based on the registry key
