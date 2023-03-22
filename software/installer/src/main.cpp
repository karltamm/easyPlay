#include "mainwindow.h"

#include <logger.h>
#include <QApplication>

int main(int argc, char* argv[]) {
  Logger::start();
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  int result = a.exec();
  Logger::stop();
  return result;
}
