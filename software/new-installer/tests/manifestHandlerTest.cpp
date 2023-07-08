#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include <gtest/gtest.h>

// TODO: create test class

#define MANIFEST_ABS_PATH R"(/Users/karl/Library/Application Support/Mozilla/NativeMessagingHosts/easyPlay.json)"

TEST(ManifestHandlerTest, CanCreateManifestFile) {
  // TODO: get home path and don't use abs path
  std::ifstream manifestFile(MANIFEST_ABS_PATH);

  // TODO: check that file can be opened (exists)

  // TODO: use path set above
  std::string expectedContent = {"{\"name\":\"easyPlay\",\"description\":\"EasyPlaydeviceclient\",\"path\":\"/Users/karl/repos/easyPlay/software/client/build/easyplay-device-client\",\"type\":\"stdio\",\"allowed_extensions\":[\"easyPlay@easyPlay\"]}"};

  std::string realContent{std::istreambuf_iterator<char>(manifestFile), std::istreambuf_iterator<char>()};
  realContent.erase(std::remove_if(realContent.begin(), realContent.end(), isspace), realContent.end());

  EXPECT_TRUE(expectedContent.compare(realContent) == 0) << "Real content:" << realContent << std::endl
                                                         << "Expected: " << expectedContent;
}