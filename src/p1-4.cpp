#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace boost;

typedef std::pair<int, int> Pair;
typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef adjacency_list<listS, vecS, directedS, no_property, EdgeWeightProperty>
    graph_t;
typedef graph_traits<graph_t>::vertex_descriptor Vertex;

int main(int, char**) {
  graph_t g;
  graph_traits<graph_t>::vertex_iterator vi, vend;
  graph_traits<graph_t>::out_edge_iterator ei, eend;
  Vertex u, v;

  // maps to go between natural label (i,j) of vertex to internal description
  std::map<Pair, Vertex> nat_to_int;
  std::map<Vertex, Pair> int_to_nat;

  //  article -> volume, article -> value maps
  std::map<int, int> art_volume;
  std::map<int, int> art_value;

  int knapsack_vol, num_articles, i, x, vol, val;
  std::ifstream infile("../p1-4.dat");
  infile >> knapsack_vol >> num_articles;
  while (infile >> i >> vol >> val) {
    art_volume.insert(std::make_pair(i, vol));
    art_value.insert(std::make_pair(i, val));
    std::cout << "article " << i << "vol, val " << vol << val << std::endl;
  }

  for (i = 0; i <= num_articles + 1; i++) {
    for (x = 0; x <= knapsack_vol; x++) {
      v = add_vertex(g);
      nat_to_int.insert(std::make_pair(Pair(i, x), v));
      int_to_nat.insert(std::make_pair(v, Pair(i, x)));
    }
  }

  // insert edges into graph
  for (i = 1; i <= num_articles; i++) {
    for (x = 0; x <= knapsack_vol; x++) {
      add_edge(nat_to_int[Pair(i - 1, x)], nat_to_int[Pair(i, x)], 0, g);
      if (x + art_volume[i] <= knapsack_vol)
        add_edge(nat_to_int[Pair(i - 1, x)],
                 nat_to_int[Pair(i, x + art_volume[i])], -1 * art_value[i], g);
    }
  }
  for (x = 0; x <= knapsack_vol; x++)
    add_edge(nat_to_int[Pair(num_articles, x)],
             nat_to_int[Pair(num_articles + 1, knapsack_vol)], 0, g);

  // set up and run bellman-ford
  Vertex s = nat_to_int[Pair(0, 0)];
  int N = num_vertices(g);
  std::vector<Vertex> p(N);
  std::vector<int> d(N);

  bool r = bellman_ford_shortest_paths(
      g, N, distance_map(&d[0]).predecessor_map(&p[0]).root_vertex(s));
  if (!r) {
    std::cerr << "Oops! Negative cycle! Bellman-Ford will not work." << std::endl;
    exit(EXIT_FAILURE);
  } else
    std::cout << "No negative cycle present." << std::endl;

  std::cout << "distances and parents:" << std::endl;
  int a, b, pa, pb;
  for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    if (*vi == p[*vi])
      continue;  // we don't care about vertices not reachable from (0, 0)
    tie(a, b) = int_to_nat[*vi];
    tie(pa, pb) = int_to_nat[p[*vi]];

    std::cout << "distance(" << a << "," << b << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << a << "," << b << ") = " << pa << "," << pb
              << std::endl;
  }
  std::cout << std::endl;

  std::vector<Vertex> path;
  std::vector<Vertex>::iterator pathit, pathend;
  u = nat_to_int[Pair(num_articles + 1, knapsack_vol)];
  while (u != p[u]) {
    path.push_back(u);
    u = p[u];
  }
  path.push_back(u);

  std::reverse(path.begin(), path.end());

  std::cout << "shortest path from (0,0) to (" << num_articles + 1 << ","
            << knapsack_vol << "):" << std::endl;
  for (pathit = path.begin(); pathit != path.end(); pathit++) {
    tie(a, b) = int_to_nat[*pathit];
    std::cout << "(" << a << "," << b << ")  ";
  }
  std::cout << std::endl;

  /* FOR DEBUGGING
  std::cout << "edges in graph:" << std::endl;
  for (tie(vi, vend) = vertices(g); vi != vend; vi++) {
    for (tie(ei, eend) = out_edges(*vi, g); ei != eend; ei++) {
      int sx, sy, tx, ty;
      tie(sx, sy) = int_to_nat[source(*ei, g)];
      tie(tx, ty) = int_to_nat[target(*ei, g)];
      std::cout << "(" << sx << "," << sy << ") -> (" << tx << "," << ty << ")"
                << " wt " << wmap[*ei] << std::endl;
    }
  }
  */

  exit(EXIT_SUCCESS);
}
