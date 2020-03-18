// #include <json/json.h>
#include <curl_client.h>

class ExampleClient {
public:
  ExampleClient();
  ~ExampleClient();
  std::pair<CURLcode, std::string> GETRequest();

private:
  SimpleCURLClient::CurlClient *m_curl_client;
  const std::string m_GET_URL =
      "https://postman-echo.com/get?foo1=bar1&foo2=bar2";
};
