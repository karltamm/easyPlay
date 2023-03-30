#ifndef COPYHANDLER_H
#define COPYHANDLER_H

#include <QObject>
#include <QStringList>

class CopyHandler : public QObject {
  Q_OBJECT
 public:
  explicit CopyHandler(QObject* parent = nullptr);

  void run();

 signals:
  void requestCopy(QStringList fileNames, QString destDirPath);
  void copyResult(bool success);

 private:
  void handleCopyRequest();
  bool copyFileToDir(QString fileName, QString dirPath);
  QString getFileAbsPath(QString fileName);
};

#endif  // COPYHANDLER_H
