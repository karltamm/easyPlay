#ifndef FIREFOXHANDLER_H
#define FIREFOXHANDLER_H

#include <QObject>
#include <QSettings>
#include <QString>

#define FIREFOX_REG_PATH        R"(HKEY_LOCAL_MACHINE\SOFTWARE\Mozilla)"
#define FIREFOX_PATH_VALUE_NAME "PathToExe"

class FirefoxHandler : public QObject {
  Q_OBJECT
 public:
  explicit FirefoxHandler(QObject* parent = nullptr);
  ~FirefoxHandler();

  bool isFirefoxInstalled();
  QString getFirefoxPath();  // TODO: rm

 private:
  QSettings* firefoxReg;
};

#endif  // FIREFOXHANDLER_H
