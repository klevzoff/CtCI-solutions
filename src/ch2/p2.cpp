#include <cassert>

#include <FwdList.hpp>

template <typename T>
T & nth_to_last(FwdList<T> const & l, size_t n)
{
  assert(l.head);
  auto lead = l.head;
  for(; n > 0; --n)
  {
    lead = lead->next;
  }
  auto tail = l.head;
  for (; lead->next; lead = lead->next, tail = tail->next);
  return tail->val;
}

int main()
{
  assert(nth_to_last<int>({1}, 0) == 1);
  assert(nth_to_last<int>({1,2}, 0) == 2);
  assert(nth_to_last<int>({1,2}, 1) == 1);
  assert(nth_to_last<int>({3,2,1}, 2) == 3);
  assert(nth_to_last<int>({3,2,1}, 1) == 2);
  assert(nth_to_last<int>({3,2,1}, 0) == 1);
}
