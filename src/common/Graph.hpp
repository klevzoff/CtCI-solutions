#ifndef CTCI_SOLUTIONS_GRAPH_HPP
#define CTCI_SOLUTIONS_GRAPH_HPP

#include <vector>
#include <tuple>
#include <initializer_list>
#include <cstdint>
#include <numeric>

/**
 * @brief A simple directed graph representation with node and edge data.
 *
 * An undirected graph can be obtained by duplicating each edge in reverse direction.
 */
template <typename NDATA = void, typename EDATA = void>
struct Graph
{
  using node_data_type = NDATA;
  using edge_data_type = EDATA;

  using node_id_type = std::uint64_t;
  using edge_id_type = std::uint64_t;

  Graph(std::initializer_list<node_data_type> node_data,
        std::initializer_list<std::tuple<node_id_type, node_id_type, edge_data_type>> const & edges)
  : node_data(node_data),
    adjacency(node_data.size())
  {
    for (auto && e : edges)
    {
      adjacency[std::get<0>(e)].push_back(std::get<1>(e));
      edge_data.push_back(std::get<2>(e));
    }
  }

  [[nodiscard]] size_t num_nodes() const { return node_data.size(); }
  [[nodiscard]] size_t num_edges() const { return edge_data.size(); }

  std::vector<node_data_type>            node_data;
  std::vector<edge_data_type>            edge_data;
  std::vector<std::vector<node_id_type>> adjacency;
};

/**
 * @brief A specialization of Graph for no-data graph (adjacency only).
 */
template <>
struct Graph<void,void>
{
  using node_id_type = std::uint64_t;
  using edge_id_type = std::uint64_t;

  Graph(size_t num_nodes,
        std::initializer_list<std::tuple<node_id_type, node_id_type>> const & edges)
      : adjacency(num_nodes)
  {
    for (auto && e : edges)
    {
      adjacency[std::get<0>(e)].push_back(std::get<1>(e));
    }
  }

  [[nodiscard]] size_t num_nodes() const
  {
    return adjacency.size();
  }

  [[nodiscard]] size_t num_edges() const
  {
    return std::accumulate(adjacency.begin(), adjacency.end(), 0,
                           [](auto n, auto const & v){ return n + v.size(); });
  }

  std::vector<std::vector<node_id_type>> adjacency;
};

#endif //CTCI_SOLUTIONS_GRAPH_HPP
