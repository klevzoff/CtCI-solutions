#include "Tree.hpp"

#include <cassert>

namespace impl
{
template<typename T>
bool check_subtree(typename BinaryTree<T>::Node const * tnode, typename BinaryTree<T>::Node const * snode)
{
  if (!tnode) return !snode;
  return tree_ops::compare(tnode, snode, std::equal_to<>{})
      || check_subtree<T>(tnode->left, snode)
      || check_subtree<T>(tnode->right, snode);
}
}

/**
 * @brief Check Subtree.
 *
 * Given two tress T1 and T2, check if T2 is a subtree of T1, i.e. there exists a node n of T1
 * s.t. the subtree of n is identical to T2 (in terms of value equality, not node identity).
 */
template<typename T>
bool check_subtree(BinaryTree<T> const & tree, BinaryTree<T> const & subtree)
{
  return impl::check_subtree<T>(tree.root, subtree.root);
}

int main()
{
  assert(check_subtree<int>({}, {}));
  assert(check_subtree<int>({{0,-1,-1,0}}, {{0,-1,-1,0}}));
  assert(check_subtree<int>({{0,1,-1,0},{1,-1,-1,1}}, {{0,-1,-1,1}}));
  assert(check_subtree<int>({{0,-1,1,0},{1,-1,-1,1}}, {{0,-1,-1,1}}));
  assert(!check_subtree<int>({{0,1,-1,0},{1,-1,-1,1}}, {{0,-1,-1,0}}));
  assert(check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, {{0,-1,-1,1}}));
  assert(check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, {{0,-1,-1,2}}));
  assert(!check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, {{0,1,-1,0},{1,-1,-1,1}}));
  assert(!check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, {{0,-1,2,0},{2,-1,-1,2}}));
  assert(check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}, {{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}));
  assert(check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,-1,-1,4}}, {{0,1,2,2},{1,-1,-1,3},{2,-1,-1,4}}));
  assert(!check_subtree<int>({{0,1,2,0},{1,-1,-1,1},{2,3,4,2},{3,-1,-1,3},{4,-1,-1,4}}, {{0,1,2,2},{1,-1,-1,3},{2,-1,3,4},{3,-1,-1,5}}));
}
