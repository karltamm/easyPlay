#ifndef FIREFOXHANDLER_H
#define FIREFOXHANDLER_H

#include <QObject>
#include <QSettings>
#include <QString>

#define FIREFOX_KEY                        R"(HKEY_LOCAL_MACHINE\SOFTWARE\Mozilla Firefox)"
#define FIREFOX_NATIVE_MESSAGING_HOSTS_KEY "NativeMessagingHosts"
#define EASYPLAY_NATIVE_APP_KEY_NAME       "easyPlay"  // Must be same as native manifest JSON "name" field

class FirefoxHandler : public QObject {
  Q_OBJECT
 public:
  explicit FirefoxHandler(QObject* parent = nullptr);
  ~FirefoxHandler();

  bool isFirefoxInstalled();
  void addNativeAppManifest(QString manifestAbsPath);

 private:
  QSettings* firefoxReg;
};

// TODO: make easyplay-native-app-manifest.json exe path relative

#endif  // FIREFOXHANDLER_H
