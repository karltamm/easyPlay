#include <QCoreApplication>

#include "browserHandler.h"
#include "deviceHandler.h"
#include "logger.h"

int main(int argc, char* argv[]) {
  Logger::start();
  QCoreApplication app(argc, argv);

  DeviceHandler deviceHandler;
  BrowserHandler browserHandler;

  QObject::connect(&deviceHandler, &DeviceHandler::rxMessage, &browserHandler, &BrowserHandler::sendToBrowser);
  QObject::connect(&browserHandler, &BrowserHandler::rxMessage, &deviceHandler, &DeviceHandler::addToTxQueue);

  int result = app.exec();
  Logger::stop();

  return result;
}
