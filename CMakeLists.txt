cmake_minimum_required(VERSION 2.6)
project(hwsix)

include_directories(${hwsix_SOURCE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wc++11-extensions -Wall -O0")
else()
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall -O0")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

add_subdirectory(src)
add_subdirectory(util)
