#include <QApplication>

#include "ui/setupWizard.h"
// TODO: add logger

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  SetupWizard setupWizard;
  setupWizard.show();

  return app.exec();
}