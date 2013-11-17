set(util_source_files
  Digraph.hpp
  Digraph.cpp
  dijkstra.hpp
  bellman-ford.hpp
  )

add_library(util ${util_source_files})
find_package(Boost 1.55 COMPONENTS graph REQUIRED)
target_link_libraries(util ${Boost_INCLUDE_DIR})
