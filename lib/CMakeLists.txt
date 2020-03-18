cmake_minimum_required(VERSION 3.10.2)

if (WIN32)
    # only need to enable
    message("On windows, using WinSSL.")
    option(CMAKE_USE_WINSSL "Set to ON to use WinSSL for windows." ON)
else()
    option(CMAKE_USE_WINSSL "Set to ON to use WinSSL for windows." OFF)
endif (WIN32)

add_subdirectory(simple_curl_cpp)
