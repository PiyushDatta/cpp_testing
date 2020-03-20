cmake_minimum_required(VERSION 3.10.2)

project(example_client_project)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)

# Options

# libcurl
if (WIN32)
    # only need to enable
    message("On windows, using WinSSL.")
    option(CMAKE_USE_WINSSL "Set to ON to use WinSSL for windows." ON)
else()
    option(CMAKE_USE_WINSSL "Set to ON to use WinSSL for windows." OFF)
endif (WIN32)

# nlohmann_json
option(USE_EXTERNAL_NLOHMANN_JSON "Use an external JSON library" OFF)
