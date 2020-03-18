#include "include/example_client.h"

int main(int argc, char const *argv[]) {
  ExampleClient example_client;
  std::pair<CURLcode, std::string> curl_resp = example_client.GETRequest();
  std::cout << curl_resp.first << '\n';
  std::cout << curl_resp.second << '\n';

  return 0;
}
