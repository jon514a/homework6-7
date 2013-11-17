#include "Digraph.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace boost;

const int INF = 2147483647;

// Computes shortest paths in Digraph g from source s to all other vertices.
// distances and parents assumed to be empty maps that will be filled in by this
// code.
// Assumes graph g has vertices labeled 0, 1, ..., nvertices-1.
// Also implicitly assumes our representation of INF is sufficiently large,
// which it is for Problem 1.1 in Schrijver.
void bellman_ford(Digraph &g, int nvertices, Vertex s,
                  std::map<Vertex, Vertex> &parents,
                  std::map<Vertex, int> &distances) {
  graph_traits<Digraph>::vertex_iterator vit, vend;
  graph_traits<Digraph>::out_edge_iterator oeit, oeend;
  graph_traits<Digraph>::edge_iterator eit, eend;
  graph_traits<Digraph>::edge_descriptor e;
  Vertex u, v;
  property_map<Digraph, edge_weight_t>::type wmap = get(edge_weight, g);
  int i;

  for (tie(vit, vend) = vertices(g); vit != vend; vit++) distances[*vit] = INF;

  distances[s] = 0;

  for (i = 1; i <= nvertices - 1; i++) {
    for (tie(eit, eend) = edges(g); eit != eend; eit++) {
      u = source(*eit, g);
      v = target(*eit, g);
      if (distances[u] + wmap[*eit] < distances[v]) {
        distances[v] = distances[u] + wmap[*eit];
        parents[v] = u;
      }
    }
  }

  // check for cycles of negative weight
  for (tie(eit, eend) = edges(g); eit != eend; eit++) {
    u = source(*eit, g);
    v = target(*eit, g);
    if (distances[u] + wmap[*eit] < distances[v])
      std::cerr << "Graph contains a cycle of negative weight. Bellman-Ford "
                   "does not apply." << std::endl;
    exit(EXIT_FAILURE);
  }
}
