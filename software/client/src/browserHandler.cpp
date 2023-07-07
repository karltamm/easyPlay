#include "browserHandler.h"

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <QJsonDocument>
#include <iostream>

#include "logger.h"

#define BIT_COUNT_IN_BYTE            8
#define BYTE_MAX_SIZE                0xff
#define BROWSER_MSG_SIZE_BYTES_COUNT 4
#define RX_MSG_POLLING_INTERVAL_MS   10

BrowserHandler::BrowserHandler(QObject* parent)
    : QObject{parent},
      rxMsgPollingTimer{new QTimer{this}} {
  this->handleRxMessages();
}

bool BrowserHandler::isStdinReady() {
  struct timespec timeout = {0};

  fd_set fileDescriptorSet;
  FD_ZERO(&fileDescriptorSet);
  FD_SET(STDIN_FILENO, &fileDescriptorSet);

  return pselect(STDIN_FILENO + 1, &fileDescriptorSet, nullptr, nullptr, &timeout, nullptr);
}

void BrowserHandler::unblockStdin() {
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

uint BrowserHandler::getRxMessageSize() {
  uint messageSize = 0;

  char byte;
  for (quint8 i = 0; i < BROWSER_MSG_SIZE_BYTES_COUNT; i++) {
    std::cin.get(byte);

    if (std::cin.fail()) {
      qWarning() << "Failed to read RX browser message size byte";
      return 0;
    }

    messageSize += (quint8)byte << (BIT_COUNT_IN_BYTE * i);
  }

  return messageSize;
}

void BrowserHandler::handleRxMessages() {
  this->unblockStdin();

  QObject::connect(this->rxMsgPollingTimer, &QTimer::timeout, this, [this]() {
    if (!this->isStdinReady()) {
      return;
    }

    uint messageSize = this->getRxMessageSize();
    std::string jsonString(messageSize, 0);
    std::cin.read(&jsonString[0], messageSize);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray::fromStdString(jsonString));

    if (jsonDocument.isEmpty()) {
      qWarning() << "RX browser message JSON is invalid:" << jsonString;
      return;
    }

    emit this->rxMessage(jsonDocument["message"].toString());

#ifdef DEBUG_BUILD
    qDebug() << "RX browser:" << jsonDocument["message"].toString();
#endif
  });

  this->rxMsgPollingTimer->start(RX_MSG_POLLING_INTERVAL_MS);
}

void BrowserHandler::sendToBrowser(const QString& message) {
  if (message.isEmpty()) {
    qWarning() << "Won't send empty message to browser";
    return;
  }

  QString data;

  QString jsonString = QObject::tr("{\"message\": \"%1\"}").arg(message);
  uint messageSize = jsonString.length();

  for (quint8 i = 0; i < BROWSER_MSG_SIZE_BYTES_COUNT; i++) {
    data.push_back(static_cast<char>(messageSize & BYTE_MAX_SIZE));  // Little endian
    messageSize >>= BIT_COUNT_IN_BYTE;
  }

  data.push_back(jsonString);

#ifdef DEBUG_BUILD
  qDebug() << "TX browser:" << data;
#endif

  std::cout << data.toStdString() << std::flush;
}