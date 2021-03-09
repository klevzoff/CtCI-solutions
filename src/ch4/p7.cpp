#include "Graph.hpp"

#include <unordered_map>
#include <queue>
#include <cassert>

template<typename T>
std::vector<T> build_order(std::vector<T> const & projects,
                           std::vector<std::pair<T,T>> const & deps)
{
  using idx_t = Graph<>::node_id_type;

  // Convert project IDs to numeric IDs (i.e. graph node indices)
  std::unordered_map<T, idx_t> proj_lookup;
  for (size_t i = 0; i < projects.size(); ++i)
    proj_lookup.emplace(projects[i], i);

  // Same conversion for dependencies
  std::vector<std::tuple<idx_t, idx_t>> adj;
  adj.reserve((deps.size()));
  for (auto const & d : deps)
    adj.emplace_back(proj_lookup.at(d.first), proj_lookup.at(d.second));

  // Make the graph
  Graph<> dag{ projects.size(), adj };

  // Count the incoming edges
  std::vector<size_t> inc_counts(dag.num_nodes(), 0);
  for (idx_t i = 0; i < dag.num_nodes(); ++i)
    for (idx_t j : dag.adjacency[i])
      ++inc_counts[j];

  // Initialize the queue
  std::queue<Graph<>::node_id_type> buildable;
  for (idx_t i = 0; i < dag.num_nodes(); ++i)
    if (inc_counts[i] == 0)
      buildable.push(i);

  // Populate the build order via topological sort of the DAG
  std::vector<T> result;
  while (!buildable.empty())
  {
    idx_t const i = buildable.front();
    result.push_back(projects[i]);
    buildable.pop();
    for (idx_t j : dag.adjacency[i])
    {
      if( --inc_counts[j] == 0)
        buildable.push(j);
    }
  }

  // If all projects handled, we have a valid build order
  return result.size() == projects.size() ? result : std::vector<T>{};
}

bool test(std::vector<char> const & projects,
          std::vector<std::pair<char,char>> const & deps,
          std::vector<char> const & expected)
{
  return build_order(projects, deps) == expected;
}

int main()
{
  assert(test({}, {}, {}));
  assert(test({'a'}, {}, {'a'}));
  assert(test({'a','b'}, {}, {'a','b'}));
  assert(test({'a','b'}, {{'a','b'}}, {'a','b'}));
  assert(test({'a','b','c'}, {{'a','b'}, {'b','c'}}, {'a','b','c'}));
  assert(test({'a','b','c'}, {{'a','b'}, {'c','b'}}, {'a','c','b'}));
  assert(test({'a','b','c'}, {{'b','a'}, {'b','c'}}, {'b','a','c'}));
  assert(test({'a','b','c'}, {{'a','b'}, {'b','c'},{'c','a'}}, {}));
}
