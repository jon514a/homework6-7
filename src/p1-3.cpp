#include "Digraph.hpp"      // located in util folder
#include "bellman-ford.hpp" // located in util folder 
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>

using namespace boost;

int main(int, char**) {
  Digraph g;
  Vertex s, t; // t is effectively a dummy 
  graph_traits<Digraph>::vertex_iterator vi, vend;
  graph_traits<Digraph>::out_edge_iterator ei, eend;

  initialize_network(std::cin, g, s,
                     t);  // "Capacities" are just weights in this
                          // case. s is root vertex; we can ignore
                          // t.
  int N = num_vertices(g);
  std::map<Vertex, Vertex> p;
  std::map<Vertex, int> d;

  bellman_ford(g, N, s, p, d);
  std::cout << "distances and parents:" << std::endl;
  for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;

  return 0;
}

