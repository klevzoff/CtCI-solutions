#include <string>
#include <cassert>

using namespace std;

/**
 * @brief Palindrome permutation.
 *
 * Given a string check if it is a permutation of a palindrome (force lowercase and ignore non-English-letter characters).
 * Time complexity: O(N).
 * Space complexity: O(1).
 */
bool is_palindrome_perm(string const & s)
{
  int32_t odd = 0;
  for (char c : s)
  {
    if ('a' <= c && c <= 'z')
    {
      int v = c - 'a';
      odd ^= 1 << v;
    }
  }
  return (odd & (odd-1)) == 0;
}

int main()
{
  assert(is_palindrome_perm(""));
  assert(is_palindrome_perm("a"));
  assert(is_palindrome_perm("aaa"));
  assert(is_palindrome_perm("baa"));
  assert(is_palindrome_perm("aabb"));
  assert(is_palindrome_perm("ababc"));
  assert(!is_palindrome_perm("abc"));
  assert(!is_palindrome_perm("aabc"));
}
