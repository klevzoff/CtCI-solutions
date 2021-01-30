#include <FwdList.hpp>

#include <cassert>
#include <utility>

using namespace std;

/**
 * @brief Sum Lists.
 *
 * Add tow numbers represented as singly linked lists of digits.
 * This version is for reverse representation (least significant digit first).
 * Time complexity: O(max(Na, Nb)).
 * Space complexity: O(1), not including space for result.
 */
template <typename T>
FwdList<T> sum_lists_reverse(FwdList<T> const & a, FwdList<T> const & b)
{
  using Node = typename FwdList<T>::Node;
  FwdList<T> r;
  auto pa = a.head;
  auto pb = b.head;
  auto pr = r.head;
  T carry = 0;
  // go over common part of both lists
  for (; pa && pb; pa = pa->next, pb = pb->next)
  {
    auto node = new Node();
    node->val = pa->val + pb->val + carry;
    if ((carry = node->val > 9)) node->val -=10;
    if (pr)
    {
      pr->next = node;
    }
    else
    {
      r.head = node;
    }
    pr = node;
  }
  // go over remaining list, if any
  auto p = pa ? pa : pb;
  for (; p; p = p->next)
  {
    auto node = new Node();
    node->val = p->val + carry;
    if ((carry = node->val > 9)) node->val -=10;
    pr->next = node;
    pr = node;
  }
  if (carry > 0)
  {
    auto node = new Node();
    node->val = carry;
    pr->next = node;
  }
  return r;
}

template <typename T>
std::pair<typename FwdList<T>::Node *, T>
sum_lists_forward_helper(typename FwdList<T>::Node * a, typename FwdList<T>::Node * b)
{
  using Node = typename FwdList<T>::Node;
  if (!a || !b) return { nullptr, 0 };
  auto [tail, carry] = sum_lists_forward_helper<T>(a->next, b->next);
  Node * node = new Node();
  node->next = tail;
  node->val = a->val + b->val + carry;
  if ((carry = node->val > 9)) node->val -=10;
  return { node, carry };
}

/**
 * @brief Sum Lists.
 *
 * Add tow numbers represented as singly linked lists of digits.
 * This version is for forward representation (most significant digit first).
 * Time complexity: O(max(Na, Nb)).
 * Space complexity: O(min(Na, Nb)), not including space for result.
 */
template <typename T>
FwdList<T> sum_lists_forward(FwdList<T> const & a, FwdList<T> const & b)
{
  using Node = typename FwdList<T>::Node;

  // compute length of each list
  int la = 0;
  for (auto n = a.head; n; n = n->next) ++la;
  int lb = 0;
  for (auto n = b.head; n; n = n->next) ++lb;

  // choose shorter/longer lists
  auto hs = la < lb ? a.head : b.head;
  auto hl = la < lb ? b.head : a.head;
  size_t const diff = abs(la - lb);

  // skip non-overlapping part of the longer list to get to the common part
  auto pl = hl;
  for (size_t i = 0; i < diff; ++i) pl = pl->next;

  // recursively add two equal-length lists
  auto [hr, carry] = sum_lists_forward_helper<T>(pl, hs);

  // build the head of result list (but reversed) by copying non-overlapping part of the longer list
  Node * rem = nullptr;
  for (auto n = hl; n != pl; n = n->next)
  {
    auto node = new Node();
    node->val = n->val;
    node->next = rem;
    rem = node;
  }

  // Add the carry and simultaneously reverse the head part
  while (rem)
  {
    rem->val += carry;
    if ((carry = rem->val > 9)) rem->val -=10;
    auto tmp = rem->next;
    rem->next = hr;
    hr = rem;
    rem = tmp;
  }

  // add extra "carry" node if needed
  if (carry > 0)
  {
    auto node = new Node();
    node->val = carry;
    node->next = hr;
    hr = node;
  }

  return FwdList<T>{ hr };
}

bool test_reverse(FwdList<int> const & a, FwdList<int> const & b, FwdList<int> const & e)
{
  return sum_lists_reverse(a, b) == e;
}

bool test_forward(FwdList<int> const & a, FwdList<int> const & b, FwdList<int> const & e)
{
  return sum_lists_forward(a, b) == e;
}

int main()
{
  assert(test_reverse({}, {}, {}));
  assert(test_reverse({1}, {1}, {2}));
  assert(test_reverse({7}, {8}, {5,1}));
  assert(test_reverse({6,1}, {5}, {1,2}));
  assert(test_reverse({5}, {6,1}, {1,2}));
  assert(test_reverse({7,1,6}, {5,9,2}, {2,1,9}));
  assert(test_reverse({9,7,8}, {6,8,5}, {5,6,4,1}));

  assert(test_forward({}, {}, {}));
  assert(test_forward({1}, {1}, {2}));
  assert(test_forward({7}, {8}, {1,5}));
  assert(test_forward({1,6}, {5}, {2,1}));
  assert(test_forward({5}, {1,6}, {2,1}));
  assert(test_forward({6,1,7}, {2,9,5}, {9,1,2}));
  assert(test_forward({8,7,9}, {5,8,6}, {1,4,6,5}));
}
