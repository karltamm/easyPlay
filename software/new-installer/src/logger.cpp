#include "logger.h"

#include <iostream>

#include <QDateTime>

#define LOGS_DIR_NAME "logs"

QPointer<QFile> Logger::logFile = QPointer<QFile>{};

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

  QDir logsDir = Logger::getLogsDir(LOGS_DIR_NAME);

  if (!logsDir.exists()) {
    qWarning() << "Logs folder doesn't exists";
    return;
  }

  QString logFilePath = logsDir.absoluteFilePath(Logger::getLogFileName());
  logFile = new QFile{logFilePath};

  if (!logFile->open(QIODevice::NewOnly | QIODevice::Text)) {
    qWarning() << "Couldn't create log file";
    Logger::stop();
    return;
  }

  qInstallMessageHandler(Logger::handleMessage);

  qInfo() << "Started logger";
}

void Logger::stop() {
  qInfo() << "Stopped logger";

  if (logFile.isNull()) {
    return;
  }

  logFile->close();
  logFile->deleteLater();
}

QDir Logger::getLogsDir(const QString& dirName) {
  QString logsDirPath = QDir::currentPath() + QDir::separator() + dirName;
  QDir logsDir{logsDirPath};

  if (!logsDir.exists() and !logsDir.mkpath(logsDirPath)) {
    qWarning() << "Logs directory unavailable";
  }

  return logsDir;
}

QString Logger::getLogFileName() {
  QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy-hh.mm.ss");
  return QString{date + ".log"};
}

void Logger::handleMessage(QtMsgType type, const QMessageLogContext& context, const QString& message) {
  QString logLine = QString{"%1 | %2 | %3 | %4 | %5 | %6\n"}
                        .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"),
                             Logger::contextNames.value(type),
                             QString::number(context.line),
                             QString{context.file}.section('/', -1),                                            // File name without file path
                             QString{context.function}.section('(', -2, -2).section(' ', -1).section(':', -1),  // Function name only
                             message);

  QTextStream{stdout} << logLine;

  logFile->write(logLine.toLocal8Bit());
  logFile->flush();
}
