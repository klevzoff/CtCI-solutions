#include <List.hpp>

#include <cassert>

/**
 * @brief Partition a list.
 *
 * Reorder a singly-linked list such that all nodes with values less than pivot
 * are before those with values higher than pivot.
 * Though not required by original problem, this partition is also stable (which simplifies testing).
 * Time complexity: O(N).
 * Space complexity: O(1).
 */
template<typename T>
void partition(FwdList<T> & l, T const pivot)
{
  using Node = typename FwdList<T>::Node;
  if (!l.head) return;

  // find the end of left partition
  Node * r = nullptr;
  for (auto n = l.head; n && n->val < pivot; r = n, n = n->next);

  // iterate over the rest and move nodes to left partition as needed
  for (Node * curr = r ? r->next : l.head->next, * prev = r ? r : l.head; curr; prev = curr, curr = curr->next)
  {
    // smaller value, move from p2 to p1
    if (curr->val < pivot)
    {
      // extract current node
      prev->next = curr->next;
      // insert just before start of p2
      if (r)
      {
        curr->next = r->next;
        r->next = curr;
      }
      else
      {
        curr->next = l.head;
        l.head = curr;
      }
      r = curr;
    }
  }
}

bool test(FwdList<int> l, int const pivot, FwdList<int> const & e)
{
  partition(l, pivot);
  return l == e;
}

int main()
{
  assert(test({}, 5, {}));
  assert(test({2,1}, 5, {2,1}));
  assert(test({6,5}, 5, {6,5}));
  assert(test({2,1,6,5}, 5, {2,1,6,5}));
  assert(test({6,5,2,1}, 5, {2,1,6,5}));
  assert(test({3,5,8,5,10,2,1}, 5, {3,2,1,5,8,5,10}));
}
