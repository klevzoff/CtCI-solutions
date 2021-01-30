#include <FwdList.hpp>

#include <cassert>
#include <unordered_set>

using namespace std;

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
  unordered_set<T> seen;
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
bool test_solution(FwdList<int> l, FwdList<int> const & e, F f)
{
  f(l);
  return l == e;
}

bool test(FwdList<int> const & l, FwdList<int> const & e)
{
  return test_solution(l, e, remove_duplicates<int>)
      && test_solution(l, e, remove_duplicates_v2<int>);
}

int main()
{
  assert(test({}, {}));
  assert(test({1}, {1}));
  assert(test({1,1,1}, {1}));
  assert(test({1,2,3}, {1,2,3}));
  assert(test({1,1,2,3}, {1,2,3}));
  assert(test({5,2,4,2,1,5,3}, {5,2,4,1,3}));
}
