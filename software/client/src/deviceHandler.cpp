#include "deviceHandler.h"

#include <QSerialPortInfo>

#include "logger.h"

#define DEVICE_USB_DESCRIPTION "EasyPlayDevice"
#define DEVICE_BAUD_RATE       QSerialPort::Baud9600
#define DEVICE_HEARTBEAT_MSG   "EP_HEARTBEAT"
#define NEW_CONNECTION_MSG     "DEVICE_CONNECTED"

#define CONNECTION_CHECK_INTERVAL_MS    1000
#define HEARTBEAT_INTERVAL_MS           1000
#define TX_QUEUE_PROCESSING_INTERVAL_MS 5
#define TX_QUEUE_POLLING_INTERVAL_MS    50

DeviceHandler::DeviceHandler(QObject* parent)
    : QObject{parent},
      serialPort{new QSerialPort{this}},
      deviceHeartbeatTimer{new QTimer{this}},
      connectionCheckTimer{new QTimer{this}},
      txQueueTimer{new QTimer{this}},
      deviceConnected{false} {
  this->handleDeviceConnection();
  this->handleRxMessages();
  this->handleDeviceHeartbeat();
  this->processTxQueue();
}

DeviceHandler::~DeviceHandler() {
  this->closeConnection();
}

void DeviceHandler::handleDeviceConnection() {
  QObject::connect(this->connectionCheckTimer, &QTimer::timeout, this, [this]() {
    QString devicePortName = this->getDevicePortName(DEVICE_USB_DESCRIPTION);

    if (devicePortName.isEmpty()) {
      qWarning() << "Didn't find the device";
      this->closeConnection();
    } else if (this->deviceConnected) {
      return;
    }

    this->connectToDevice(devicePortName);
  });

  this->connectionCheckTimer->start(CONNECTION_CHECK_INTERVAL_MS);
}

void DeviceHandler::connectToDevice(const QString& portName) {
  qInfo() << "Trying to connect to the device";

  this->serialPort->setBaudRate(DEVICE_BAUD_RATE);
  this->serialPort->setPortName(portName);
  this->deviceConnected = this->serialPort->open(QSerialPort::ReadWrite);

  if (this->deviceConnected) {
    qInfo() << "Connected to the device";
    emit this->rxMessage(NEW_CONNECTION_MSG);
  } else {
    qWarning() << "Couldn't connect to the device";
  }
}

QString DeviceHandler::getDevicePortName(const QString& deviceDescription) {
  for (auto& port : QSerialPortInfo::availablePorts()) {
    if (port.description().compare(deviceDescription) == 0) {
      return port.portName();
    }
  }

  return {};
}

void DeviceHandler::handleDeviceHeartbeat() {
  QObject::connect(this->deviceHeartbeatTimer, &QTimer::timeout, this, [this]() {
    if (!this->deviceConnected) {
      return;
    }

    this->addToTxQueue(DEVICE_HEARTBEAT_MSG);
  });

  this->deviceHeartbeatTimer->start(HEARTBEAT_INTERVAL_MS);
}

void DeviceHandler::sendToDevice(const QString& message) {
  if (!this->deviceConnected) {
    qWarning() << "Can't send message to device as it's not connected";
    return;
  }

  if (this->serialPort->write(message.toUtf8()) < 0) {
    qWarning() << "Message sending failed";
    closeConnection();
  }
}

void DeviceHandler::handleRxMessages() {
  QObject::connect(this->serialPort, &QSerialPort::readyRead, this, [this]() {
    emit this->rxMessage(QString{this->serialPort->readAll()});
  });
}

void DeviceHandler::closeConnection() {
  qInfo() << "Closing device connection";
  this->deviceConnected = false;
  this->serialPort->close();
}

void DeviceHandler::addToTxQueue(const QString& message) {
  this->txQueue.enqueue(message);
}

void DeviceHandler::processTxQueue() {
  QObject::connect(this->txQueueTimer, &QTimer::timeout, this, [this]() {
    if (this->txQueue.isEmpty()) {
      this->txQueueTimer->setInterval(TX_QUEUE_POLLING_INTERVAL_MS);
      return;
    }

    this->sendToDevice(this->txQueue.dequeue());
    this->txQueueTimer->setInterval(TX_QUEUE_PROCESSING_INTERVAL_MS);
  });

  this->txQueueTimer->start(TX_QUEUE_POLLING_INTERVAL_MS);
}