#include <QApplication>

#include "logger.h"
#include "ui/setupWizard.h"

int main(int argc, char* argv[]) {
  Logger::start();
  QApplication app(argc, argv);

  SetupWizard setupWizard;
  setupWizard.show();

  int result = app.exec();
  Logger::stop();

  return result;
}