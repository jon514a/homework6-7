#include "Digraph.hpp"
#include <fstream>
#include <iostream>

using namespace boost;

int main(int, char **) {
  Digraph g;
  Vertex s, t;
  Digraph::vertex_iterator vit, vend;
  Digraph::out_edge_iterator nbrit, nbrend;

  std::ifstream infile("../test.in");
  initialize_network(infile, g, s, t);
  // get capacities (stored as properties of edges in g)
  property_map<Digraph, edge_weight_t>::type capacity = get(edge_weight, g);

  long mf = max_flow_min_cut(s, t, g);
  std::cout << "max flow: " << mf << std::endl;

  return 0;
}
