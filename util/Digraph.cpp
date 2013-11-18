#include "Digraph.hpp"

using namespace boost;

void initialize_network(std::istream &in, Digraph &g, Vertex &s, Vertex &t) {
  int i, j, c;

  // source and sink are first two lines of file
  in >> i >> j;
  s = vertex(i, g);
  t = vertex(j, g);

  // get edges and capacities
  while (in >> i >> j >> c) boost::add_edge(i, j, c, g);

  return;
}

Digraph create_aux_graph(Flow &f, Digraph &g) {
  Digraph auxg;
  Digraph::out_edge_iterator eit, eend;
  Digraph::vertex_iterator vit, vend;
  Digraph::vertex_descriptor v;

  boost::tie(vit, vend) = boost::vertices(g);
  property_map<Digraph, edge_weight_t>::type capacity = get(edge_weight, g);

  for (; vit != vend; vit++) {
    tie(eit, eend) = out_edges(*vit, g);
    for (; eit != eend; eit++) {
      v = target(*eit, g);

      if (get(capacity, *eit) > f[*eit]) {
        add_edge(*vit, v, 1, auxg);
      }
      if (f[*eit] > 0) {
        add_edge(v, *vit, 1, auxg);
      }
    }
  }

  return auxg;
}

int max_flow_min_cut(Vertex &s, Vertex &t, Digraph &g) {
  Digraph::out_edge_iterator e, eend;
  Digraph::vertex_iterator v, vend;
  std::vector<Vertex> cut(num_vertices(g));
  bool isCut = false;
  Flow f;
  // initialize flow
  for (tie(v, vend) = vertices(g); v != vend; v++)
    for (tie(e, eend) = out_edges(*v, g); e != eend; e++) std::make_pair(*e, 0);

  for (; !isCut;) {
    cut.clear();
    tie(cut, isCut) = flow_augmenting_path(s, t, f, g);
  }

  int flowval = 0;
  for (tie(e, eend) = out_edges(s, g); e != eend; e++) {
    flowval += f[*e];
  }

  std::cout << "Ford-Fulkerson found the following maximum-valued flow:"
            << std::endl;
  for (tie(v, vend) = vertices(g); v != vend; v++) {
    for (tie(e, eend) = out_edges(*v, g); e != eend; e++) {
      std::cout << "edge (" << source(*e, g) << "," << target(*e, g)
                << ") has flow " << f[*e] << std::endl;
    }
  }
  std::cout << std::endl;

  std::cout << "Ford-Fulkerson also found the following minimum s-t cut set:"
            << std::endl;
  std::vector<Vertex>::iterator cutit;
  for (cutit = cut.begin(); cutit != cut.end(); cutit++)
    std::cout << "cut vertex: " << *cutit << std::endl;
  std::cout << std::endl;

  return flowval;
}

std::pair<std::vector<Vertex>, bool> flow_augmenting_path(Vertex &s, Vertex &t,
                                                          Flow &f, Digraph &g) {
  Vertex u, v;
  std::vector<Vertex>::iterator uit, vit;
  Digraph auxg = create_aux_graph(f, g);

  // find s-t path in auxg
  std::vector<Vertex> p(num_vertices(auxg));
  std::vector<int> d(num_vertices(auxg));
  dijkstra_shortest_paths(auxg, s, predecessor_map(&p[0]).distance_map(&d[0]));
  std::vector<Vertex> st_path_or_cut;

  // no s-t path exists, so return a cut
  if (p[t] == t) {
    Digraph::vertex_iterator vgit, vend;
    st_path_or_cut.push_back(s);
    for (tie(vgit, vend) = vertices(g); vgit != vend; vgit++)
      if (p[*vgit] != *vgit) st_path_or_cut.push_back(*vgit);
    return std::make_pair(st_path_or_cut, true);
  }

  st_path_or_cut.push_back(t);

  for (v = t, u = p[t]; u != v; u = p[u], v = p[v]) st_path_or_cut.push_back(u);
  std::reverse(st_path_or_cut.begin(), st_path_or_cut.end());

  // augment flow appropriately
  Edge e;

  uit = st_path_or_cut.begin();
  vit = uit + 1;

  long sigma =
      -1;  // setting sigma = -1 here is a hack (see the for loop below)
  // get min capacity along path
  bool found;
  for (uit = st_path_or_cut.begin(), vit = uit + 1; vit != st_path_or_cut.end();
       uit++, vit++) {
    long c;
    tie(e, found) = edge(*uit, *vit, g);
    if (found)
      c = get(edge_weight, g, e) - f[e];
    else {
      Edge e1 = edge(*vit, *uit, g).first;
      c = f[e1];
    }
    if (c < sigma || sigma == -1) sigma = c;
  }
  // std::cout << "sigma is now " << sigma << std::endl;

  // augment path
  Digraph::edge_descriptor e_g;
  for (uit = st_path_or_cut.begin(), vit = uit + 1; vit != st_path_or_cut.end();
       uit++, vit++) {
    tie(e_g, found) = edge(*uit, *vit, g);
    if (found) f[e_g] += sigma;
    tie(e_g, found) = edge(*vit, *uit, g);
    if (found) f[e_g] -= sigma;
  }

  return std::make_pair(st_path_or_cut, false);
}
