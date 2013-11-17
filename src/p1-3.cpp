#include "Digraph.hpp"
#include "bellman-ford.hpp"
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

  std::ifstream infile("../p1-3.dat");

  initialize_network(infile, g, s, t);  // "Capacities" are just weights in this
                                        // case. s is root vertex; we can ignore
                                        // t.
  int N = num_vertices(g);
  //std::vector<Vertex> p(N);
  //std::vector<int> d(N);
  std::map<Vertex, Vertex> p;
  std::map<Vertex, int> d;

  //bool r = bellman_ford_shortest_paths(
  //    g, N, distance_map(&d[0]).predecessor_map(&p[0]).root_vertex(s));
  //if (!r) std::cout << "negative cycle!" << std::endl;
  //else std::cout << "no negative cycle present" << std::endl;
  bellman_ford(g, N, s, p, d);
  std::cout << "distances and parents:" << std::endl;
  for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;

  //std::cout << "edges in graph:" << std::endl;
  //for (tie(vi, vend) = vertices(g); vi != vend; vi++)
  //  for (tie(ei, eend) = out_edges(*vi, g); ei != eend; ei++)
  //    std::cout << source(*ei, g) << "," << target(*ei, g) << " wt " << wmap[*ei] << std::endl;

  return 0;
}

