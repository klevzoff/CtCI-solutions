#include <cassert>
#include <unordered_set>

#include <List.hpp>

using namespace std;

/**
 * @brief Remove Dups.
 *
 * Remove duplicate elements in an unsorted linked list.
 */
template <typename T>
void remove_duplicates(List<T> & l)
{
  unordered_set<T> seen;
  for (auto curr = l.head; curr; curr = curr->next)
  {
    if (seen.count(curr->val) > 0)
    {
      curr->prev->next = curr->next;
      if (curr->next) curr->next->prev = curr->prev;
      auto tmp = curr;
      curr = curr->prev;
      delete tmp;
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
 * O(n2) without using additional memory (hash set).
 */
template <typename T>
void remove_duplicates_v2(List<T> & l)
{
  for (auto curr = l.head; curr; curr = curr->next)
  {
    auto s = l.head;
    for (; s != curr && s->val != curr->val; s = s->next);
    if (s != curr)
    {
      curr->prev->next = curr->next;
      if (curr->next) curr->next->prev = curr->prev;
      auto tmp = curr;
      curr = curr->prev;
      delete tmp;
    }
  }
}

template <typename F>
bool test_solution(List<int> l, List<int> const & e, F f)
{
  f(l);
  return l == e;
}

bool test(List<int> const & l, List<int> const & e)
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
