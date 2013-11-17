#include "Digraph.hpp"

using namespace boost;

int main() {
  Digraph g;
  Vertex s, t;
  initialize_network(std::cin, g, s, t);
  int flow = max_flow_min_cut(s, t, g);

  std::cout << "total flow: " << flow << std::endl;

  return 0;
}
