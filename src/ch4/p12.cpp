#include "Tree.hpp"
#include "testing.hpp"

#include <unordered_map>

namespace impl
{
template<typename T>
size_t num_paths_with_sum(typename BinaryTree<T>::Node const * const node,
                          T const & target_sum,
                          T const current_sum,
                          std::unordered_map<T, size_t> & num_nodes)
{
  if (!node) return 0;
  ++num_nodes[current_sum];
  T const new_sum = current_sum + node->value;
  size_t const num_paths = num_nodes[new_sum - target_sum]
                         + num_paths_with_sum(node->left, target_sum, new_sum, num_nodes)
                         + num_paths_with_sum(node->right, target_sum, new_sum, num_nodes);
  --num_nodes[current_sum];
  return num_paths;
}
}

/**
 * @brief Paths With Sum.
 *
 * Given a binary tree with integer values, find the number of tree paths that sum to a given value.
 * Paths don't have to start on the root or end on a leaf node, but must go downwards.
 */
template<typename T>
size_t num_paths_with_sum(BinaryTree<T> const & tree, T const & target_sum)
{
  std::unordered_map<T, size_t> num_nodes{};
  return impl::num_paths_with_sum<T>(tree.root, target_sum, 0, num_nodes);
}

int main()
{
  EXPECT_EQ(num_paths_with_sum<int>({}, 0), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({}, 1), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,-1,-1,1}}, 1), 1u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,-1,-1,1}}, 0), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,-1,-1,1}}, 2), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}}, -1), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}},  0), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}},  1), 1u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}},  2), 1u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}},  3), 2u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}},  4), 1u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,-1,-1,2},{2,-1,-1,3}},  5), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}}, -2), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}}, -1), 1u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}},  0), 0u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}},  1), 3u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}},  2), 2u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}},  3), 3u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}},  4), 2u);
  EXPECT_EQ(num_paths_with_sum<int>({{0,1,2,1},{1,3,4,2},{2,-1,-1,3},{3,-1,-1,1},{4,-1,-1,-1}},  5), 0u);
  return testing::summary();
}
