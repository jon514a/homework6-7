cmake_minimum_required(VERSION 2.6)
project(hwsix)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wc++11-extensions -Wall -O0")

add_subdirectory(src)
add_subdirectory(util)


#include_directories(util)
#link_directories(${hwsix_BINARY_DIR})
#add_library(Digraph util/Digraph.cpp)
#
#FIND_PACKAGE( Boost 1.54 COMPONENTS graph REQUIRED )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
#
#ADD_EXECUTABLE( p11 p1-1/p-1.cpp )
#
#TARGET_LINK_LIBRARIES(Digraph ${Boost_LIBRARIES})
#TARGET_LINK_LIBRARIES( p11 ${Boost_LIBRARIES} Digraph )
