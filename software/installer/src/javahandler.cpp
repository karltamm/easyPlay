#include "javahandler.h"

#include <logger.h>
#include <QProcess>

JavaHandler::JavaHandler(QObject* parent)
    : QObject{parent},
      versionRegex(new QRegularExpression(VERSION_NUM_REGEX_PATTERN)) {
}

JavaHandler::~JavaHandler() {
  delete versionRegex;
}

bool JavaHandler::isSuitableJreInstalled(int minVersion) {
  return getJreVersion() >= minVersion;
}

int JavaHandler::getJreVersion() {
  QProcess process;
  process.start("java --version");
  if (!process.waitForFinished(JAVA_PROCESS_TIMEOUT_MS)) {
    qWarning() << "Java version number detection timeout";
    return 0;
  }
  QString output = process.readAllStandardOutput();
  QRegularExpressionMatch match = versionRegex->match(output);
  if (match.hasMatch()) {
    return match.captured().split(".")[0].toInt();
  }
  return 0;
}
