cmake_minimum_required(VERSION 2.6)
project(hwsix_src)

#set(hwsix_source_files p1-1.cpp p1-3.cpp p1-4.cpp p4-7ii.cpp)
include_directories(${hwsix_SOURCE_DIR}/util)
link_directories(${hwsix_SOURCE_DIR}/util)

add_executable(p11 p1-1.cpp)
add_executable(p13 p1-3.cpp)
add_executable(p14 p1-4.cpp)
add_executable(p47 p4-7ii.cpp)

target_link_libraries(p11 util)
target_link_libraries(p13 util)
target_link_libraries(p14 util)
target_link_libraries(p47 util)
