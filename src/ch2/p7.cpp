#include <FwdList.hpp>

#include <cassert>

/**
 * @brief Intersection.
 *
 * Detect if two lists have a common node (which means they have an entire common suffix/tail).
 * Nodes are compared by identity (reference/pointer) and not stored value.
 * Return the intersecting node.
 * Time complexity: O(max(Na, Nb))
 * Space complexity: O(1)
 */
template <typename T>
typename FwdList<T>::Node *
check_intersection(typename FwdList<T>::Node * a, typename FwdList<T>::Node * b)
{
  using Node = typename FwdList<T>::Node;

  // Compute the length of each list
  int la = 0;
  for (auto n = a; n; n = n->next) ++la;
  int lb = 0;
  for (auto n = b; n; n = n->next) ++lb;

  // Assign longer/shorter list pointers
  Node * ps = la < lb ? a : b;
  Node * pl = la < lb ? b : a;

  // Skip nodes of the longer list
  for (int i = 0; i < abs(la - lb); ++i) pl = pl->next;

  // Find the shared node
  Node * shared = nullptr;
  for (; pl && ps; pl = pl->next, ps = ps->next)
  {
    if (pl == ps)
    {
      shared = pl;
      break;
    }
  }
  return shared;
}

/**
 * The test is constructed from two input lists and a number as follows:
 *  - if n < 0, lists are passed to algorithm as is and nullptr is the expected answer;
 *  - if n >= 0, tail of list b is "attached" to n-th node of list a and that node is the expected answer.
 * At the end, list b is detached to allow for safe destruction.
 */
bool test(FwdList<int> const & a, FwdList<int> const & b, int n)
{
  if (n < 0) return check_intersection<int>(a.head, b.head) == nullptr;

  auto node = a.head;
  for (; n > 0 && node; --n) node = node->next;

  if (b.head)
  {
    auto blast = b.head;
    for (; blast && blast->next; blast = blast->next);
    blast->next = node;
    bool res = check_intersection<int>(a.head, b.head) == node;
    blast->next = nullptr;
    return res;
  }
  else
  {
    return check_intersection<int>(a.head, node) == node;
  }
}

int main()
{
  assert(test({},{},-1));
  assert(test({1,2},{3,4},-1));
  assert(test({1,2,3},{4,5,6},1));
  assert(test({1,2,3},{},1));
  assert(test({1},{2,3},0));
  assert(test({1,2,3},{1},2));
}
