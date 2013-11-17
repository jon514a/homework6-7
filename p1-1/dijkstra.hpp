#include "Digraph.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace boost;

const int INF = 100000;

// Computes shortest paths in Digraph g from source s to all other vertices.
// distances and parents assumed to be empty maps that will be filled in by this
// code.
// Assumes graph g has vertices labeled 0, 1, ..., nvertices-1.
// Also implicitly assumes our representation of INF is sufficiently large,
// which it is for Problem 1.1 in Schrijver.
void dijkstra(Digraph &g, int nvertices, Vertex s,
              std::map<Vertex, Vertex> &parents,
              std::map<Vertex, int> &distances) {
  graph_traits<Digraph>::vertex_iterator vit, vend;
  graph_traits<Digraph>::out_edge_iterator eit, eend;
  graph_traits<Digraph>::edge_descriptor e;
  Vertex u, v;
  property_map<Digraph, edge_weight_t>::type wmap = get(edge_weight, g);
  int d;

  // use a lambda for compare
  auto comp = [&](Vertex & a, Vertex & b)->int {
    return distances[a] > distances[b];
  }
  ;
  auto unvisited = std::vector<Vertex>();
  std::map<Vertex, bool> unvisited_map;
  std::make_heap(unvisited.begin(), unvisited.end(), comp);

  for (tie(vit, vend) = vertices(g); vit != vend; vit++) distances[*vit] = INF;

  for (tie(vit, vend) = vertices(g); vit != vend; vit++) {
    unvisited.push_back(*vit);
    std::push_heap(unvisited.begin(), unvisited.end(), comp);
    unvisited_map[*vit] = true;
  }

  parents[s] = s;
  distances[s] = 0;
  while (!unvisited.empty()) {
    u = unvisited.front();
    std::pop_heap(unvisited.begin(), unvisited.end(), comp);
    unvisited.pop_back();

    if (distances[u] == INF) break;

    for (tie(eit, eend) = out_edges(u, g); eit != eend; eit++) {
      v = target(*eit, g);
      if (unvisited_map[v]) {
        d = distances[u] + wmap[*eit];
        if (distances[v] > d) {
          distances[v] = d;
          parents[v] = u;
        }
      }
    }

    unvisited_map[u] = false;
    std::make_heap(unvisited.begin(), unvisited.end(),
                   comp);  // this is a hack!  inefficient
  }
}
