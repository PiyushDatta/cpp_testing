cmake_minimum_required(VERSION 3.10.2)

project(example_client)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)
