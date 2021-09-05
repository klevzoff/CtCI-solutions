#include "Tree.hpp"
#include "testing.hpp"

#include <cassert>

namespace impl
{
template<typename T>
std::pair<bool, int> is_balanced_impl(typename BinaryTree<T>::Node const * const node)
{
  if (!node) return { true, 0 };
  auto [bl, dl] = is_balanced_impl<T>(node->left);
  if (!bl) return { false, dl };
  auto [br, dr] = is_balanced_impl<T>(node->right);
  return { br && std::abs(dl - dr) <= 1, std::max(dl, dr) + 1 };
}
}

template<typename T>
bool is_balanced(BinaryTree<T> const & tree)
{
  return impl::is_balanced_impl<T>(tree.root).first;
}

int main()
{
  EXPECT(is_balanced<int>({}));
  EXPECT(is_balanced<int>({{0,-1,-1,0}}));
  EXPECT(is_balanced<int>({{0,1,-1,0},{1,-1,-1,1}}));
  EXPECT(is_balanced<int>({{0,-1,2,0},{2,-1,-1,2}}));
  EXPECT(is_balanced<int>({{0,1,2,0},{1,-1,-1,1},{2,-1,-1,2}}));
  EXPECT(!is_balanced<int>({{0,1,-1,0},{1,2,-1,1},{2,-1,-1,2}}));
  EXPECT(!is_balanced<int>({{0,1,-1,0},{1,-1,2,1},{2,-1,-1,2}}));
  EXPECT(is_balanced<int>({{0,1,3,0},{1,2,-1,1},{2,-1,-1,2},{3,-1,-1,3}}));
  EXPECT(is_balanced<int>({{0,1,3,0},{1,2,-1,1},{2,-1,-1,2},{3,-1,4,3},{4,-1,-1,4}}));
  return testing::summary();
}
