#ifndef JAVAHANDLER_H
#define JAVAHANDLER_H

#include <QObject>
#include <QRegularExpression>
#include <QString>

#define JRE_MIN_VERSION           17
#define JAVA_PROCESS_TIMEOUT_MS   500
#define VERSION_NUM_REGEX_PATTERN R"(\b\d+\.\d+\.\d+\b)"

class JavaHandler : public QObject {
  Q_OBJECT
 public:
  explicit JavaHandler(QObject* parent = nullptr);
  ~JavaHandler();

  bool isSuitableJreInstalled(int minVersion);

 private:
  QRegularExpression* versionRegex;

  int getJreVersion();
};

#endif  // JAVAHANDLER_H
