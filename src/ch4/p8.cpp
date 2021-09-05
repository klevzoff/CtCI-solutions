#include "Tree.hpp"
#include "testing.hpp"

namespace impl
{
template<typename T>
typename BinaryTree<T>::Node const *
common_ancestor(typename BinaryTree<T>::Node const * const node,
                typename BinaryTree<T>::Node const * a,
                typename BinaryTree<T>::Node const * b)
{
  using Node = typename BinaryTree<T>::Node;

  // trivial cases to terminate recursion
  if (!node) return nullptr;
  if (node == a || node == b) return node;

  // search left subtree and remove the node found from further search
  Node const * const lres = common_ancestor<T>(node->left, a, b);
  if (lres == a) a = nullptr;
  if (lres == b) b = nullptr;
  if (!a && !b) return lres;

  // search right subtree and choose the common ancestor
  Node const * const rres = common_ancestor<T>(node->right, a, b);
  return rres ? (lres ? node : rres) : lres;
}
}

/**
 * @brief Find Common Ancestor.
 *
 * Given a tree and two nodes, find their common ancestor.
 * (According to book hints, the tree doesn't have parent links).
 *
 * @note We interpret each node as being a (0-distance) ancestor to itself.
 */
template<typename T>
typename BinaryTree<T>::Node const *
common_ancestor(BinaryTree<T> const & tree,
                typename BinaryTree<T>::Node const * a,
                typename BinaryTree<T>::Node const * b)
{
  return impl::common_ancestor<T>(tree.root, a, b);
}

/**
 * For testing purposes, we take _values_ of the target nodes and find them first.
 * This assumes values in the input tree are all unique.
 */
void test(BinaryTree<int> const & tree, int a, int b, int c)
{
  BinaryTree<int>::Node const * na = tree.find(a);
  BinaryTree<int>::Node const * nb = tree.find(b);
  BinaryTree<int>::Node const * nc = tree.find(c);
  EXPECT_EQ(nc, common_ancestor<int>(tree, na, nb));
}

int main()
{
  test({{0,-1,-1,0}}, 0, 0, 0);
  test({{0,1,-1,0},{1,-1,-1,1}}, 0, 1, 0);
  test({{0,1,-1,0},{1,-1,-1,1}}, 1, 0, 0);
  test({{0,-1,1,0},{1,-1,-1,1}}, 0, 1, 0);
  test({{0,-1,1,0},{1,-1,-1,1}}, 1, 0, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, 1, 2, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, 2, 1, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 1, 2, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 1, 3, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 1, 4, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 1, 5, 0);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 2, 4, 2);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 2, 5, 2);
  test({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,5,-1,4},{5,-1,-1,5}}, 3, 5, 2);
  return testing::summary();
}
