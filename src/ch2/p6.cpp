#include <FwdList.hpp>

#include <cassert>
#include <utility>

template <typename T>
std::pair<typename FwdList<T>::Node *, bool>
is_palindrome_recursive(typename FwdList<T>::Node * start, size_t len)
{
  if (len == 0) return { start, true };
  if (len == 1) return { start->next, true };
  auto [end, result] = is_palindrome_recursive<T>(start->next, len - 2);
  return { end->next, result && start->val == end->val };
}

/**
 * @brief Is Palindrome.
 *
 * Check if a singly-linked list is a palindrome.
 * This is a recursive solution from the book just for practice.
 * I believe it loses to a stack-based solution (same asymptotic complexity, worse multipliers).
 * Time complexity: O(N).
 * Space complexity: O(N).
 */
template <typename T>
bool is_palindrome(FwdList<T> const & l)
{
  size_t len = 0;
  for (auto n = l.head; n; n = n->next) ++len;
  auto [_, result] = is_palindrome_recursive<T>(l.head, len);
  return result;
}

int main()
{
  assert(is_palindrome<int>({}));
  assert(is_palindrome<int>({1}));
  assert(is_palindrome<int>({1,2,1}));
  assert(is_palindrome<int>({2,1,1,2}));
  assert(is_palindrome<int>({3,5,1,5,3}));
  assert(!is_palindrome<int>({1,2}));
  assert(!is_palindrome<int>({1,2,3}));
  assert(!is_palindrome<int>({2,3,1,4,2}));
}
