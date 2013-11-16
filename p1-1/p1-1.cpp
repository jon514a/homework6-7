#include "Digraph.hpp"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>

using namespace boost;

int main(int, char **) {
  Digraph g;
  Vertex v, s, t;
  graph_traits<Digraph>::vertex_iterator vi, vend;

  std::ifstream infile("../p1-1.dat");

  initialize_network(infile, g, s, t);  // "Capacities" are just weights in this
                                        // case. We want shortest path from s to
                                        // t.

  std::vector<Vertex> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));

  dijkstra_shortest_paths(
      g, s, predecessor_map(
                make_iterator_property_map(p.begin(), get(vertex_index, g)))
                .distance_map(make_iterator_property_map(
                     d.begin(), get(boost::vertex_index, g))));

  std::cout << "distances and parents:" << std::endl;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;

  // reconstruct shortest s-t path (0-16 path, in this case)
  std::cout << "shortest s-t path" << std::endl;
  std::vector<Vertex> stpath;
  std::vector<Vertex>::iterator pathit;
  for (v = t; v != s; v = p[v]) stpath.push_back(v);
  stpath.push_back(s);
  std::reverse(stpath.begin(), stpath.end());
  for (pathit = stpath.begin(); pathit != stpath.end(); pathit++)
    std::cout << *pathit << " ";
  std::cout << std::endl << std::endl;

  std::cout << "s-t distance: " << d[t] << std::endl;
  return 0;
}
