cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    example_client.cc
)

set(HEADERS
    include/example_client.h
)

add_executable(example_client main.cc ${SOURCES} ${HEADERS})
target_link_libraries(example_client simple_curl_cpp nlohmann_json::nlohmann_json)
