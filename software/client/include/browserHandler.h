#ifndef BROWSER_HANDLER_H
#define BROWSER_HANDLER_H

#include <QObject>
#include <QTimer>

class BrowserHandler : public QObject {
  Q_OBJECT
 public:
  explicit BrowserHandler(QObject* parent = nullptr);

  void sendToBrowser(const QString& message);

 signals:
  void rxMessage(QString message);

 private:
  QTimer* rxMsgPollingTimer;

  void handleRxMessages();
  bool isStdinReady();
  void unblockStdin();
  uint getRxMessageSize();
};

#endif  // BROWSER_HANDLER_H