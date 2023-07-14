#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QPointer>

class Logger {
 public:
  static void start();
  static void stop();

 private:
  static QHash<QtMsgType, QString> contextNames;
  static QPointer<QFile> logFile;

  static QDir getLogsDir(const QString& dirName);
  static QString getLogFileName();
  static void handleMessage(QtMsgType type, const QMessageLogContext& context, const QString& message);
};

#endif  // LOGGER_H
