#ifndef DEVICE_HANDLER_H
#define DEVICE_HANDLER_H

#include <QObject>
#include <QPointer>
#include <QQueue>
#include <QSerialPort>
#include <QTimer>

class DeviceHandler : public QObject {
  Q_OBJECT
 public:
  explicit DeviceHandler(QObject* parent = nullptr);
  ~DeviceHandler();

  void addToTxQueue(const QString& message);

 signals:
  void rxMessage(QString message);

 private:
  QQueue<QString> txQueue;
  QSerialPort* serialPort;
  QTimer* deviceHeartbeatTimer;
  QTimer* connectionCheckTimer;
  QTimer* txQueueTimer;
  bool deviceConnected;

  void handleDeviceConnection();
  void connectToDevice(const QString& portName);
  QString getDevicePortName(const QString& deviceDescription);
  void handleDeviceHeartbeat();
  void handleRxMessages();
  void closeConnection();
  void processTxQueue();
  void sendToDevice(const QString& message);
};

#endif  // DEVICE_HANDLER_H