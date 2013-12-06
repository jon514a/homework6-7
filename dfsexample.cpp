// clang++ -L/usr/local/Cellar/boost/1.54.0/lib -lboost_graph-mt
// -I/usr/local/Cellar/boost/1.54/include -o dfsex dfsexample.cpp
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;

typedef property<edge_weight_t, int> EdgeWeightProperty;

typedef boost::adjacency_list<listS, vecS, undirectedS, no_property,
                              EdgeWeightProperty> mygraph;

typedef boost::graph_traits<mygraph>::vertex_descriptor Vertex;
typedef boost::property_map<mygraph, boost::vertex_index_t>::type IndexMap;
typedef boost::iterator_property_map<Vertex *, IndexMap, Vertex, Vertex &>
    PredecessorMap;

class custom_dfs_visitor : public boost::default_dfs_visitor {
 public:
  template <typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph &g) const {
    std::cout << "At " << u << std::endl;
  }
  template <typename Edge, typename Graph>
  void examine_edge(Edge e, const Graph &g) const {
    std::cout << "Examining edges " << e << std::endl;
  }
};

class custom_bfs_visitor : public boost::default_bfs_visitor {
 public:
  template <typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph &g) const {
    std::vector<Vertex> v;
    std::cout << "ohhai! i'm at " << u << std::endl;
    v.push_back(u);
  }
};

template <typename ParentsMap>
class parents_bfs_visitor : public boost::default_bfs_visitor {
 public:
  parents_bfs_visitor(ParentsMap &p) : m_p(p) {}

  template <typename Edge, typename Graph>
  void tree_edge(Edge e, const Graph &g) const {
    m_p[target(e, g)] = source(e, g);
  }

  std::vector<mygraph::vertex_descriptor> &m_p;
};

int main() {
  mygraph g;
  add_edge(0, 1, 1, g);
  add_edge(0, 3, -1, g);
  add_edge(1, 2, 1, g);
  add_edge(2, 3, -1, g);
  add_edge(3, 1, 1, g);
  add_edge(1, 3, -1, g);
  add_edge(1, 4, 1, g);
  add_edge(3, 5, -1, g);

  // DFS example
  //custom_dfs_visitor vis;
  // depth_first_search(g, visitor(vis));

  // lame BFS example
  // custom_bfs_visitor vis2;
  // breadth_first_search(g, vertex(0, g), visitor(vis2));

  // a better BFS visitor example
  std::vector<mygraph::vertex_descriptor> p(num_vertices(g));
  parents_bfs_visitor<std::vector<mygraph::vertex_descriptor> > pvis(p);
  breadth_first_search(g, vertex(0, g), visitor(pvis));

  /*
  std::vector<mygraph::vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));

  p[vertex(0, g)] = vertex(0, g);

  dijkstra_shortest_paths(g, vertex(0, g),
                          predecessor_map(&p[0]).distance_map(&d[0]));

  std::cout << "distances and parents:" << std::endl;
  */
  graph_traits<mygraph>::vertex_iterator vi, vend;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    // std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;
}
