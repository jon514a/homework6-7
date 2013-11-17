set(util_source_files
  Digraph.hpp
  Digraph.cpp
  dijkstra.hpp
  bellman-ford.hpp
  )

find_package(Boost 1.54 COMPONENTS graph REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_library(util ${util_source_files})
target_link_libraries(util ${Boost_LIBRARIES})
