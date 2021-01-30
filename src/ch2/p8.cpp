#include <FwdList.hpp>

#include <cassert>

/**
 * @brief Loop Detection.
 *
 * Given a singly linked list that contains a loop, return the node at the start of the loop.
 * Time complexity: O(N).
 * Space complexity: O(1).
 */
template <typename T>
typename FwdList<T>::Node *
find_loop_start(FwdList<T> const & l)
{
  using Node = typename FwdList<T>::Node;

  // Create a dummy starting node to initialize search
  Node dummy;
  dummy.next = l.head;

  // Launch fast/slow pointers until they meet
  Node * pf = &dummy;
  Node * ps = &dummy;
  do
  {
    ps = ps->next;
    pf = pf->next;
    if (!pf) return nullptr;
    pf = pf->next;
    if (!pf) return nullptr;
  }
  while (pf != ps);

  // Launch another pointer from start until it meets ps
  for (auto p = &dummy; p != ps; p = p->next, ps = ps->next);

  return ps;
}

/**
 * Test is constructed as follows: given a valid (non-cicular) list and a number n,
 * we attach the tail node of the list to its n-th node to create a loop, and expect n-th node as answer.
 * At the end, tail is detached to ensure safe destruction.
 */
bool test(FwdList<int> l, int n)
{
  using Node = FwdList<int>::Node;
  Node * nth = nullptr;
  Node * last = l.head;
  int k = 0;
  for (; last && last->next; last = last->next, ++k)
  {
    if (k == n) nth = last;
  }
  if (k == n) nth = last;
  if (nth) last->next = nth;
  bool res = find_loop_start(l) == nth;
  if (nth) last->next = nullptr;
  return res;
}

int main()
{
  assert(test({}, -1));
  assert(test({1}, 0));
  assert(test({1,2,3}, -1));
  assert(test({1,2,3}, 1));
  assert(test({1,2,3,4,5,6}, 4));
  assert(test({1,2,3,4,5,6,7}, 1));
  assert(test({1,2,3,4,5,6,7}, 0));
}
