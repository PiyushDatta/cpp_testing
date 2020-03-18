#include "include/example_client.h"

ExampleClient::ExampleClient() {
  m_curl_client = new SimpleCURLClient::CurlClient(m_GET_URL);
};

ExampleClient::~ExampleClient(){};

std::pair<CURLcode, std::string> ExampleClient::GETRequest() {
  return m_curl_client.sendGETRequest();
};