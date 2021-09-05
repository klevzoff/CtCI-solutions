#include "Tree.hpp"
#include "testing.hpp"

#include <tuple>

namespace impl
{
template<typename T>
std::tuple<bool, T, T> is_bst(typename BinaryTree<T>::Node const * const node)
{
  T min = node->value;
  T max = node->value;
  bool bst = true;
  if (node->left)
  {
    auto [lbst, lmin, lmax] = is_bst<T>(node->left);
    bst &= lbst && lmax <= node->value;
    min = std::min(min, lmin);
    max = std::max(max, lmax);
  }
  if (node->right)
  {
    auto [rbst, rmin, rmax] = is_bst<T>(node->right);
    bst &= rbst && rmin > node->value;
    min = std::min(min, rmin);
    max = std::max(max, rmax);
  }

  return { bst, min, max };
}
}

/**
 * @brief Validate BST.
 *
 * For a given tree, check if it is a valid binary search tree.
 */
template<typename T>
bool is_bst(BinaryTree<T> const & tree)
{
  if (!tree.root) return true;
  return std::get<0>(impl::is_bst<T>(tree.root));
}

int main()
{
  EXPECT(is_bst<int>({}));
  EXPECT(is_bst<int>({{0,-1,-1,0}}));
  EXPECT(is_bst<int>({{0,1,-1,0},{1,-1,-1,-1}}));
  EXPECT(!is_bst<int>({{0,1,-1,0},{1,-1,-1,1}}));
  EXPECT(!is_bst<int>({{0,-1,1,0},{1,-1,-1,-1}}));
  EXPECT(is_bst<int>({{0,-1,1,0},{1,-1,-1,1}}));
  EXPECT(is_bst<int>({{0,1,2,0},{1,-1,-1,-1},{2,-1,-1,2}}));
  EXPECT(is_bst<int>({{0,1,2,0},{1,-1,-1,-1},{2,-1,3,2},{3,-1,-1,3}}));
  EXPECT(!is_bst<int>({{0,1,2,0},{1,-1,-1,-1},{2,3,-1,2},{3,-1,-1,3}}));
  EXPECT(is_bst<int>({{0,1,2,0},{1,-1,-1,-1},{2,4,3,2},{3,-1,-1,3},{4,-1,-1,1}}));
  EXPECT(!is_bst<int>({{0,1,2,0},{1,-1,-1,-1},{2,4,3,2},{3,-1,-1,3},{4,-1,-1,3}}));
  return testing::summary();
}
