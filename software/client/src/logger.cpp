#include "logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QObject>
#include <iostream>

QPointer<QFile> Logger::logFile = QPointer<QFile>();

QHash<QtMsgType, QString> Logger::contextNames = {{QtMsgType::QtDebugMsg, "D"},     //
                                                  {QtMsgType::QtInfoMsg, "I"},      //
                                                  {QtMsgType::QtWarningMsg, "W"},   //
                                                  {QtMsgType::QtCriticalMsg, "C"},  //
                                                  {QtMsgType::QtFatalMsg, "F"}};    //

void Logger::start() {
  if (!logFile.isNull()) {
    qWarning() << "Logger is already running";
    return;
  }

  QString logsDirPath = Logger::getLogsDirAbsPath("logs");

  if (logsDirPath.isEmpty()) {
    qWarning() << "Logs folder doesn't exists";
    return;
  }

  QString logFilePath = QDir::cleanPath(logsDirPath + QDir::separator() + Logger::getLogFileName());
  logFile = new QFile(logFilePath);

  if (!logFile->open(QIODevice::NewOnly | QIODevice::Text)) {
    qWarning() << "Couldn't create log file";
    Logger::stop();
    return;
  }

  qInstallMessageHandler(Logger::handleMessage);
}

void Logger::stop() {
  if (logFile.isNull()) {
    return;
  }

  logFile->close();
  logFile->deleteLater();
}

QString Logger::getLogsDirAbsPath(const QString& dirName) {
  QString logsDirPath = QDir::cleanPath(QDir::currentPath() + QDir::separator() + dirName);

  if (QDir(logsDirPath).exists()) {
    return logsDirPath;
  }

  if (QDir().mkpath(logsDirPath)) {
    return logsDirPath;
  }

  return "";
}

QString Logger::getLogFileName() {
  QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy-hh.mm.ss");
  return QString(date + ".log");
}

void Logger::handleMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
  QString message = QObject::tr("%1 | %2 | %3 | %4 | %5 | %6\n")
                        .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"))  //
                        .arg(Logger::contextNames.value(type))                              //
                        .arg(context.line)                                                  //
                        .arg(QString(context.file).section('/', -1))                        // File name without file path
                        .arg(QString(context.function)
                                 .section('(', -2, -2)  // Function name only
                                 .section(' ', -1)      //
                                 .section(':', -1))     //
                        .arg(msg);

  logFile->write(message.toLocal8Bit());
  logFile->flush();
}
