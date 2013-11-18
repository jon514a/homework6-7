#include "Digraph.hpp"  // located in util folder; 
                        // contains implementation of Ford-Fulkerson

using namespace boost;

int main() {
  Digraph g;
  Vertex s, t;
  initialize_network(std::cin, g, s, t);
  int flow = max_flow_min_cut(s, t, g);

  std::cout << "value of maximum flow: " << flow << std::endl;

  return 0;
}
