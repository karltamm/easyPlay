#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

#include <gtest/gtest.h>
#include <QString>

#include "browserHandler.h"
#include "deviceHandler.h"

#define BROWSER_MSG_SIZE_BYTES_COUNT 4
#define TEMP_STDOUT_FILE_NAME        "tempStdout.txt"

class BrowserHandlerTest : public testing::Test {
 public:
  DeviceHandler deviceHandler;
  BrowserHandler browserHandler;

  std::streambuf* originalStdout;

  virtual void SetUp() override {
    originalStdout = std::cout.rdbuf();
    QObject::connect(&deviceHandler, &DeviceHandler::rxMessage, &browserHandler, &BrowserHandler::sendToBrowser);
  }

  virtual void TearDown() override {}

  void testMessage(const std::string& message) {
    std::ofstream writeStream{TEMP_STDOUT_FILE_NAME};
    std::ifstream readStream{TEMP_STDOUT_FILE_NAME};

    std::cout.rdbuf(writeStream.rdbuf());

    this->deviceHandler.rxMessage(QString::fromStdString(message));
    std::cout.rdbuf(originalStdout);

    std::string expectedString = this->createExpectedString(message);
    std::string realString{(std::istreambuf_iterator<char>(readStream)), std::istreambuf_iterator<char>()};

    EXPECT_TRUE(expectedString.compare(realString) == 0) << "Failed to send message: \"" << message << "\"" << std::endl
                                                         << "Expected: \"" << expectedString << "\"" << std::endl
                                                         << "Real: \"" << realString << "\"";

    writeStream.close();
    readStream.close();
  }

  std::string createExpectedString(const std::string& message) {
    if (!message.size()) {
      return {};
    }

    std::string expectedString;

    std::ostringstream payloadStream;
    payloadStream << "{\"message\": \"" << message << "\"}";
    auto payload = payloadStream.str();

    auto payloadLength = payload.length();
    expectedString.resize(BROWSER_MSG_SIZE_BYTES_COUNT);
    std::memcpy(&expectedString[0], &payloadLength, BROWSER_MSG_SIZE_BYTES_COUNT);

    expectedString.append(payload);

    return std::move(expectedString);
  }
};

TEST_F(BrowserHandlerTest, CanSendMessagesToBrowser) {
  this->testMessage("TEST_EXAMPLE_1");
  this->testMessage("TEST_EXAMPLE_2");
  this->testMessage("abc");
  this->testMessage("");
}