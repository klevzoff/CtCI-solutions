#ifndef CTCI_SOLUTIONS_GRAPH_HPP
#define CTCI_SOLUTIONS_GRAPH_HPP

#include <vector>
#include <tuple>
#include <initializer_list>
#include <cstdint>
#include <numeric>

template <typename NDATA = void, typename EDATA = void>
struct Graph
{
  using ndata_t = NDATA;
  using edata_t = EDATA;

  using nidx_t = std::uint64_t;
  using eidx_t = std::uint64_t;

  Graph(std::initializer_list<ndata_t> node_data,
        std::initializer_list<std::tuple<nidx_t, nidx_t, edata_t>> const & edges)
  : node_data(node_data),
    adjacency(node_data.size())
  {
    for (auto && e : edges)
    {
      adjacency[std::get<0>(e)].push_back(std::get<1>(e));
      edge_data.push_back(std::get<2>(e));
    }
  }

  size_t num_nodes() const { return node_data.size(); }
  size_t num_edges() const { return edge_data.size(); }

  std::vector<ndata_t>             node_data;
  std::vector<edata_t>             edge_data;
  std::vector<std::vector<nidx_t>> adjacency;
};

template <>
struct Graph<void,void>
{
  using nidx_t = std::uint64_t;
  using eidx_t = std::uint64_t;

  Graph(size_t num_nodes,
        std::initializer_list<std::tuple<nidx_t, nidx_t>> const & edges)
      : adjacency(num_nodes)
  {
    for (auto && e : edges)
    {
      adjacency[std::get<0>(e)].push_back(std::get<1>(e));
    }
  }

  size_t num_nodes() const
  {
    return adjacency.size();
  }

  size_t num_edges() const
  {
    return std::accumulate(adjacency.begin(), adjacency.end(), 0,
                           [](auto n, auto const & v){ return n + v.size(); });
  }

  std::vector<std::vector<nidx_t>> adjacency;
};

#endif //CTCI_SOLUTIONS_GRAPH_HPP
