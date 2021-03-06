#include "Graph.hpp"

#include <cassert>
#include <queue>

/**
 * @brief Route Between Nodes.
 *
 * Given a directed graph, check if there is a route between two nodes.
 */
template<typename N, typename E>
bool has_path(Graph<N,E> const & g,
              typename Graph<N,E>::node_id_type src,
              typename Graph<N,E>::node_id_type dst)
{
  using nid_t = typename Graph<N,E>::node_id_type;
  assert(src < g.num_nodes() && dst < g.num_nodes());

  std::vector<bool> visited(g.num_nodes(), false);
  std::queue<nid_t> next({src});

  while (!next.empty())
  {
    nid_t const n = next.front();
    next.pop();
    if (n == dst) return true;
    visited[n] = true;
    for (auto && m : g.adjacency[n])
    {
      if (!visited[m]) next.push(m);
    }
  }
  return false;
}

int main()
{
  assert(has_path(Graph<>(1, {}), 0, 0));
  assert(!has_path(Graph<>(2, {}), 0, 1));
  assert(has_path(Graph<>(2, {{0,1}}), 0, 1));
  assert(!has_path(Graph<>(2, {{0,1}}), 1, 0));
  assert(!has_path(Graph<>(2, {{1,0}}), 0, 1));
  assert(has_path(Graph<>(2, {{1,0}}), 1, 0));
  assert(has_path(Graph<>(5, {{0,1},{1,2},{1,3},{0,3},{3,4}}), 0, 4));
  assert(has_path(Graph<>(5, {{0,1},{1,2},{1,3},{3,0},{3,4}}), 0, 4));
  assert(!has_path(Graph<>(5, {{0,1},{1,2},{3,1},{3,0},{3,4}}), 0, 4));
}
