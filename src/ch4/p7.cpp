#include "Graph.hpp"
#include "testing.hpp"
#include "printing.hpp"

#include <unordered_map>
#include <queue>

/**
 * @brief Build Order.
 *
 * Given a list of projects and a list of dependencies (pairs where second project depends on first),
 * find a valid build order in which each project is build after its dependencies. If there is no
 * valid build order, return an error.
 *
 * @note Here we return an empty list instead of throwing an exception or returning an additional error indicator.
 *       This makes testing a bit easier, but using other error reporting mechanisms is a trivial change.
 * @note We use Graph class to handle construction of adjacency representation suitable for this problem.
 *       The code to construct a vector<vector> is rather simple and could also just be pasted here.
 */
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
      if (--inc_counts[j] == 0)
        buildable.push(j);
    }
  }

  // If all projects handled, we have a valid build order
  return result.size() == projects.size() ? result : std::vector<T>{};
}

void test(std::vector<char> const & projects,
          std::vector<std::pair<char,char>> const & deps,
          std::vector<char> const & expected)
{
  EXPECT_EQ(build_order(projects, deps), expected);
}

int main()
{
  test({}, {}, {});
  test({'a'}, {}, {'a'});
  test({'a','b'}, {}, {'a','b'});
  test({'a','b'}, {{'a','b'}}, {'a','b'});
  test({'a','b','c'}, {{'a','b'}, {'b','c'}}, {'a','b','c'});
  test({'a','b','c'}, {{'a','b'}, {'c','b'}}, {'a','c','b'});
  test({'a','b','c'}, {{'b','a'}, {'b','c'}}, {'b','a','c'});
  test({'a','b','c'}, {{'a','b'}, {'b','c'},{'c','a'}}, {});
  return testing::summary();
}
