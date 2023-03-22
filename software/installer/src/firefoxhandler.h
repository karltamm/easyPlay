#ifndef FIREFOXHANDLER_H
#define FIREFOXHANDLER_H

#include <QObject>
#include <QSettings>
#include <QString>

#define MOZILLA_REGISTRY_KEY         R"(HKEY_LOCAL_MACHINE\SOFTWARE\Mozilla)"
#define FIREFOX_REGISTRY_KEY         R"(HKEY_LOCAL_MACHINE\SOFTWARE\Mozilla\Mozilla Firefox)"
#define EASYPLAY_NATIVE_APP_NAME     "easyPlay"  // Must be same as native manifest JSON "name" field
#define EASYPLAY_NATIVE_APP_KEY_NAME "NativeMessagingHosts/" EASYPLAY_NATIVE_APP_NAME "/."

class FirefoxHandler : public QObject {
  Q_OBJECT
 public:
  explicit FirefoxHandler(QObject* parent = nullptr);
  ~FirefoxHandler();

  bool isFirefoxInstalled();
  void addNativeAppManifest(QString manifestAbsPath);

 private:
  QSettings* mozillaRegistry;
};

// TODO: make easyplay-native-app-manifest.json exe path relative

#endif  // FIREFOXHANDLER_H
