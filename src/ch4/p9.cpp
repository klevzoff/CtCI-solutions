#include "Tree.hpp"

#include <vector>
#include <algorithm>
#include <cassert>

namespace impl
{
template<typename Iter>
std::vector<std::vector<typename std::iterator_traits<Iter>::value_type>>
mix_sequences(Iter s1, Iter e1, Iter s2, Iter e2)
{
  using T = typename std::iterator_traits<Iter>::value_type;
  if (s1 == e1) return { std::vector<T>(s2, e2) };
  if (s2 == e2) return { std::vector<T>(s1, e1) };

  auto const r1 = mix_sequences(std::next(s1), e1, s2, e2);
  auto const r2 = mix_sequences(s1, e1, std::next(s2), e2);

  std::vector<std::vector<T>> res;
  res.reserve(r1.size() + r2.size());

  for (std::vector<T> const & s : r1)
  {
    std::vector<T> & r = res.emplace_back(1, *s1);
    r.insert(r.end(), s.begin(), s.end());
  }
  for (std::vector<T> const & s : r2)
  {
    std::vector<T> & r = res.emplace_back(1, *s2);
    r.insert(r.end(), s.begin(), s.end());
  }

  return res;
}

template<typename T>
std::vector<std::vector<T>> bst_sequences(typename BinaryTree<T>::Node const * const node)
{
  if (!node) return {};
  auto const lres = bst_sequences<T>(node->left);
  auto const rres = bst_sequences<T>(node->right);

  // mix and match
  std::vector<std::vector<T>> res;
  if (lres.empty() && rres.empty())
  {
    res.emplace_back(1, node->value);
  }
  else if (rres.empty())
  {
    for (std::vector<T> const & lseq : lres)
    {
      std::vector<T> & r = res.emplace_back(1, node->value);
      r.insert(r.end(), lseq.begin(), lseq.end());
    }
  }
  else if (lres.empty())
  {
    for (std::vector<T> const & rseq : rres)
    {
      std::vector<T> & r = res.emplace_back(1, node->value);
      r.insert(r.end(), rseq.begin(), rseq.end());
    }
  }
  else
  {
    for (std::vector<T> const & lseq : lres)
    {
      for (std::vector<T> const & rseq : rres)
      {
        auto const mix = mix_sequences(lseq.begin(), lseq.end(), rseq.begin(), rseq.end());
        for (std::vector<T> const & mseq : mix)
        {
          std::vector<T> & r = res.emplace_back(1, node->value);
          r.insert(r.end(), mseq.begin(), mseq.end());
        }
      }
    }
  }
  return res;
}
}

/**
 * @brief BST Sequences.
 *
 * Given a binary search tree with unique values, produce all possible sequences
 * of inserted values that could have resulted in this specific tree.
 */
template<typename T>
std::vector<std::vector<T>> bst_sequences(BinaryTree<T> const & tree)
{
  return impl::bst_sequences<T>(tree.root);
}

bool test(BinaryTree<int> const & tree, std::vector<std::vector<int>> expected)
{
  std::vector<std::vector<int>> result = bst_sequences(tree);
  std::sort(result.begin(), result.end());
  std::sort(expected.begin(), expected.end());
  return result == expected;
}

int main()
{
  assert(test({}, {}));
  assert(test({{0,-1,-1,2}}, {{2}}));
  assert(test({{0,1,2,2},{1,-1,-1,1},{2,-1,-1,3}}, {{2,1,3},{2,3,1}}));
  assert(test({{0,1,2,2},{1,-1,-1,1},{2,-1,3,4},{3,-1,-1,5}}, {{2,1,4,5},{2,4,5,1},{2,4,1,5}}));
  assert(test({{0,1,2,2},{1,-1,-1,1},{2,4,3,4},{3,-1,-1,5},{4,-1,-1,3}}, {{2,1,4,3,5},{2,1,4,5,3},{2,4,3,5,1},{2,4,3,1,5},{2,4,5,3,1},{2,4,5,1,3},{2,4,1,3,5},{2,4,1,5,3}}));
}
