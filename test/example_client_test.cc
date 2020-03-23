#include "../src/example_client/testing_curl/include/example_client.h"
#include <gtest/gtest.h>
#include <string>

const std::string HEADER_GET_URL = "https://postman-echo.com/headers";
const std::string GET_URL = "https://postman-echo.com/get?foo1=bar1&foo2=bar2";
const std::string POST_URL = "https://postman-echo.com/post";
const std::string DELETE_URL = "https://postman-echo.com/delete";
std::string actual_resp = "";

class ExampleClientTest : public testing::Test {
public:
  ExampleClient *ex_client;

  virtual void SetUp() { ex_client = new ExampleClient(); }

  virtual void TearDown() { delete ex_client; }
};

TEST_F(ExampleClientTest, GetRequest) {
  std::cout << "here! Tests worked!!";
  //   EXPECT_EQ(GET_URL, trade_api->getAccount());
}
