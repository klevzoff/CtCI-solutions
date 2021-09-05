#include "Tree.hpp"
#include "testing.hpp"
#include "printing.hpp"

#include <vector>
#include <cassert>
#include <cmath>
#include <numeric>

namespace impl
{
template<typename T, typename Iter>
typename BinaryTree<T>::Node * make_min_tree(Iter first, Iter last)
{
  using Node = typename BinaryTree<T>::Node;
  if (first == last) return nullptr;
  Iter const mid = first + std::distance(first, last) / 2;
  Node * node = new Node;
  node->value = *mid;
  node->left = make_min_tree<T>(first, mid);
  node->right = make_min_tree<T>(mid + 1, last);
  return node;
}
}

/**
 * @brief Minimal Tree.
 *
 * Given a sorted (increasing order) of unique values, make a
 * binary search tree with minimal height.
 */
template<typename T>
BinaryTree<T> make_min_tree(std::vector<T> const & input)
{
  BinaryTree<T> res;
  res.root = impl::make_min_tree<T>(input.begin(), input.end());
  return res;
}

void test(std::vector<int> const & input)
{
  auto res = make_min_tree(input);
  EXPECT_EQ(res.size(), input.size());
  EXPECT_EQ(res.depth(), (input.empty() ? 0 : size_t(std::log2(input.size()))+1));
  EXPECT_EQ(res.values(), input);
}

std::vector<int> make_input(size_t const len)
{
  std::vector<int> res(len);
  std::iota(res.begin(), res.end(), 1);
  return res;
}

int main()
{
  test({});
  test({1});
  test({1,2});
  test({1,2,3});
  test({1,2,3,4,5});
  test({1,2,3,4,5,6});
  test({1,2,3,4,5,6,7});
  test({1,2,3,4,5,6,7,8});
  test({1,2,3,4,5,6,7,8,9});
  test(make_input(14));
  test(make_input(15));
  test(make_input(16));
  test(make_input(30));
  test(make_input(31));
  test(make_input(32));
  return testing::summary();
}
