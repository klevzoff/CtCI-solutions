#include "List.hpp"
#include "testing.hpp"

#include <unordered_set>

/**
 * @brief Remove Dups.
 *
 * Remove duplicate elements in an unsorted linked list.
 * Time complexity: O(N).
 * Space complexity: O(N) (or number of unique values to be precise).
 */
template <typename T>
void remove_duplicates(FwdList<T> & l)
{
  using Node = typename FwdList<T>::Node;
  std::unordered_set<T> seen;
  for (Node * curr = l.head, * prev = nullptr; curr; prev = curr, curr = curr->next)
  {
    if (seen.count(curr->val) > 0)
    {
      prev->next = curr->next;
      delete curr;
      curr = prev;
    }
    else
    {
      seen.insert(curr->val);
    }
  }
}

/**
 * @brief Remove Dups.
 *
 * Remove duplicate elements in an unsorted linked list.
 * Time complexity: O(N^2).
 * Space complexity: O(1).
 */
template <typename T>
void remove_duplicates_v2(FwdList<T> & l)
{
  using Node = typename FwdList<T>::Node;
  for (Node * curr = l.head, * prev = nullptr; curr; prev = curr, curr = curr->next)
  {
    auto s = l.head;
    for (; s != curr && s->val != curr->val; s = s->next);
    if (s != curr)
    {
      prev->next = curr->next;
      delete curr;
      curr = prev;
    }
  }
}

template <typename F>
void test_solution(FwdList<int> l, FwdList<int> const & e, F f)
{
  f(l);
  EXPECT_EQ(l, e);
}

void test(FwdList<int> const & l, FwdList<int> const & e)
{
  test_solution(l, e, remove_duplicates<int>);
  test_solution(l, e, remove_duplicates_v2<int>);
}

int main()
{
  test({}, {});
  test({1}, {1});
  test({1,1,1}, {1});
  test({1,2,3}, {1,2,3});
  test({1,1,2,3}, {1,2,3});
  test({5,2,4,2,1,5,3}, {5,2,4,1,3});
  return testing::summary();
}
