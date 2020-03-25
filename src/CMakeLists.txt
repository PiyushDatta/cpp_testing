cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    example_client/server_socket/server_socket.cc
    utils/util_functions.cc
)

set(HEADERS
    example_client/server_socket/include/server_socket.h
    utils/include/util_functions.h
)

add_library(example_client_lib ${SOURCES} ${HEADERS})
#target_link_libraries(example_client_lib PUBLIC simple_curl_cpp nlohmann_json::nlohmann_json)

add_executable(example_client main.cc)
target_link_libraries(example_client PRIVATE example_client_lib)

#target_link_libraries(example_client PRIVATE simple_curl_cpp nlohmann_json::nlohmann_json example_client_lib)
