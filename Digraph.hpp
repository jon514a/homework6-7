#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace boost;

typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef adjacency_list<listS, vecS, directedS, no_property, EdgeWeightProperty>
    Digraph;
typedef Digraph::edge_descriptor Edge;
typedef Digraph::vertex_descriptor Vertex;
typedef std::map<Edge, int> Flow;

void initialize_network(std::istream &in, Digraph &g, Vertex &s, Vertex &t);

int max_flow_min_cut(Vertex &s, Vertex &t, Digraph &g);

Digraph create_aux_graph(Flow &f, Digraph &g);

std::pair<std::vector<Vertex>, bool> flow_augmenting_path(Vertex &s, Vertex &t,
                                                          Flow &f, Digraph &g);
#endif
