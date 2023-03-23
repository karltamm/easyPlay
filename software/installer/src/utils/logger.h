#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QPointer>

class Logger {
 public:
  static void start();
  static void stop();
  static void handleMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

 private:
  static QPointer<QFile> logFile;
  static QHash<QtMsgType, QString> contextNames;

  static QString getLogsDirAbsPath(QString dirName);
  static QString getLogFileName();
};

#endif  // LOGGER_H
