#include <logger.h>
#include <setupwizard.h>
#include <QApplication>

int main(int argc, char* argv[]) {
  Logger::start();
  QApplication app(argc, argv);
  SetupWizard setupWizard;
  setupWizard.show();
  int result = app.exec();
  Logger::stop();
  return result;
}
