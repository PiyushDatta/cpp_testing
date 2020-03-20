cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    example_client_test.cc
    ../src/example_client/example_client.cc
)

set(HEADERS
    ../src/example_client/include/example_client.h
)

# googletest
enable_testing()

add_executable(example_client_test "main.cc" ${SOURCES} ${HEADERS})
target_link_libraries(example_client_test simple_curl_cpp nlohmann_json::nlohmann_json gtest)

add_test(
    NAME example_client_test
    COMMAND example_client_test
)
