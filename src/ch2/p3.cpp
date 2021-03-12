#include <List.hpp>

#include <cassert>

/**
 * @brief Delete Middle Node.
 *
 * Delete a middle (not first or last) node from a list given only pointer to that node.
 * Time complexity: O(1).
 * Space complexity: O(1).
 *
 * NB: this is a hacky solution from CtCI; I don't like it because:
 *   - it invalidates existing pointers/references to next node or its value
 *   - it requires the stored type be at least movable
 * IMO list manipulations should apply to nodes exclusively and not touch values.
 * Under that condition, the problem is not solvable in less than O(N).
 */
template <typename T>
void delete_middle_node(FwdList<T> & l, typename FwdList<T>::Node * node)
{
  (void)l; // not used
  auto next = node->next;
  assert(next); // check precondition that node is not last
  node->val = std::move(next->val);
  node->next = next->next;
  delete next;
}

bool test(FwdList<int> l, size_t i, FwdList<int> const & e)
{
  auto node = l.head;
  for (; i > 0; --i) node = node->next;
  delete_middle_node(l, node);
  return l == e;
}

int main()
{
  assert(test({1,2,3}, 1, {1,3}));
  assert(test({1,2,3,4}, 1, {1,3,4}));
  assert(test({1,2,3,4}, 2, {1,2,4}));
}
