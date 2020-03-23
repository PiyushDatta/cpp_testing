#include "example_client/testing_curl/include/example_client.h"
#include <nlohmann/json.hpp>

int main(int argc, char const *argv[]) {
  ExampleClient example_client;
  std::pair<CURLcode, std::string> curl_resp = example_client.GETRequest();

  // got a good json parsable response
  try {
    nlohmann::json m_json_data = nlohmann::json::parse(curl_resp.second);
    std::cout << "\nSuccessfully parsed JSON data" << '\n';
    std::cout << "\nJSON data size: " << m_json_data.size() << '\n';
    std::cout << "\nJSON data received:" << '\n';
    std::cout << m_json_data << '\n';
  } catch (const nlohmann::json::exception &e) {
    std::cout << "ERROR: Could not parse HTTP data as JSON" << '\n';
    // output exception information
    std::cout << "ERROR: " << e.what() << '\n';
    std::cout << "Exception id: " << e.id << '\n';
  }

  return 0;
}
