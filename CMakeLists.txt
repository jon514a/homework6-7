cmake_minimum_required(VERSION 2.6)
project(hwsix)

include_directories(${hwsix_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wc++11-extensions -Wall -O0")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

add_subdirectory(src)
add_subdirectory(util)
