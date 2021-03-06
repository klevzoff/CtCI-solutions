#include "Tree.hpp"
#include "List.hpp"

#include <cassert>

namespace detail
{
template<typename T>
void make_level_lists_impl(typename BinaryTree<T>::Node * const node,
                           std::vector<List<T>> & lists,
                           size_t level)
{
  if (!node) return;
  if (level == lists.size())
  {
    lists.push_back({});
  }
  lists[level].add_tail(node->value);
  make_level_lists_impl(node->left, lists, level+1);
  make_level_lists_impl(node->right, lists, level+1);
}
}

/**
 * @brief List of depths
 *
 * Given a binary tree, make linked lists of nodes at each depth (one per level).
 *
 * @note To facilitate testing, here we create lists of _values_ stored at the nodes,
 *       rather than the nodes themselves (in Java this is easy since everything is
 *       a reference, but in C++, we'd have to store pointers to tree nodes, and it
 *       would take manual effort to build the "correct" answer to compare against).
 *
 * @note We use doubly-linked lists here which give us free insertion at the end.
 *       So does the solution in the book (using Java's LinkedList). If a singly-linked
 *       list was requested, we'd have to track list tails in the vector as well.
 */
template<typename T>
std::vector<List<T>> make_level_lists(BinaryTree<T> const & tree)
{
  std::vector<List<T>> result;
  detail::make_level_lists_impl(tree.root, result, 0);
  return result;
}

bool test(BinaryTree<int> const & tree,
          std::vector<List<int>> const & expected)
{
  return make_level_lists(tree) == expected;
}

int main()
{
  assert(test({}, {}));
  assert(test({{0,-1,-1,0}}, {{0}}));
  assert(test({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, {{0},{1,2}}));
  assert(test({{0,1,2,0},{1,-1,-1,1},{2,3,-1,2},{3,-1,-1,3}}, {{0},{1,2},{3}}));
  assert(test({{0,1,2,0},{1,-1,4,1},{2,3,-1,2},{3,-1,-1,3},{4,-1,-1,4}}, {{0},{1,2},{4,3}}));
  assert(test({{0,1,2,0},{1,-1,4,1},{2,3,-1,2},{3,-1,5,3},{4,-1,-1,4},{5,-1,-1,5}}, {{0},{1,2},{4,3},{5}}));
}
