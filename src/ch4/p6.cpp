#include "Tree.hpp"

template<typename T>
typename BinaryPTree<T>::Node const *
find_successor(typename BinaryPTree<T>::Node const * const node)
{
  using Node = typename BinaryPTree<T>::Node;
  if (!node) return nullptr;
  if (node->right)
  {
    // successor is leftmost node in the right subtree
    Node const * curr = node->right;
    for (; curr->left; curr = curr->left);
    return curr;
  }
  else
  {
    // successor is first parent that we return to from its left subtree
    Node const * curr = node;
    while (curr->parent)
    {
      if (curr == curr->parent->left) return curr->parent;
      curr = curr->parent;
    }
    return nullptr;
  }
}

bool test(BinaryPTree<int> const & tree, int val, int succ_val)
{
  BinaryPTree<int>::Node const * const node = tree.find_bst(val);
  BinaryPTree<int>::Node const * const succ = tree.find_bst(succ_val);
  return find_successor<int>(node) == succ;
}

int main()
{
  assert(test({}, 0, 1));
  assert(test({{0,-1,-1,0}}, 0, 1));
  assert(test({{0,-1,1,0},{1,-1,-1,1}}, 0, 1));
  assert(test({{0,1,-1,1},{1,-1,-1,0}}, 0, 1));
  assert(test({{0,1,4,8},{1,2,3,4},{2,-1,-1,2},{3,-1,-1,6},{4,-1,5,10},{5,-1,-1,20}}, 4, 6));
  assert(test({{0,1,4,8},{1,2,3,4},{2,-1,-1,2},{3,-1,-1,6},{4,-1,5,10},{5,-1,-1,20}}, 2, 4));
  assert(test({{0,1,4,8},{1,2,3,4},{2,-1,-1,2},{3,-1,-1,6},{4,-1,5,10},{5,-1,-1,20}}, 6, 8));
  assert(test({{0,1,4,8},{1,2,3,4},{2,-1,-1,2},{3,-1,-1,6},{4,-1,5,10},{5,-1,-1,20}}, 8, 10));
  assert(test({{0,1,4,8},{1,2,3,4},{2,-1,-1,2},{3,-1,-1,6},{4,-1,5,10},{5,-1,-1,20}}, 10, 20));
  assert(test({{0,1,4,8},{1,2,3,4},{2,-1,-1,2},{3,-1,-1,6},{4,-1,5,10},{5,-1,-1,20}}, 20, -1));

}
