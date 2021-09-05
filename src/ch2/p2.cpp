#include "List.hpp"
#include "testing.hpp"

#include <cassert>

/**
 * @brief N-th to Last.
 *
 * Find n-th to last element of a singly-linked list.
 * Time complexity: O(N).
 * Space complexity: O(1).
 */
template <typename T>
T nth_to_last(FwdList<T> const & l, size_t n)
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
  EXPECT_EQ(nth_to_last<int>({1}, 0), 1);
  EXPECT_EQ(nth_to_last<int>({1,2}, 0), 2);
  EXPECT_EQ(nth_to_last<int>({1,2}, 1), 1);
  EXPECT_EQ(nth_to_last<int>({3,2,1}, 2), 3);
  EXPECT_EQ(nth_to_last<int>({3,2,1}, 1), 2);
  EXPECT_EQ(nth_to_last<int>({3,2,1}, 0), 1);
  return testing::summary();
}
