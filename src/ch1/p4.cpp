#include "testing.hpp"

#include <string>

/**
 * @brief Palindrome permutation.
 *
 * Given a string check if it is a permutation of a palindrome (force lowercase and ignore non-English-letter characters).
 * Time complexity: O(N).
 * Space complexity: O(1).
 */
bool is_palindrome_perm(std::string const & s)
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
  EXPECT(is_palindrome_perm(""));
  EXPECT(is_palindrome_perm("a"));
  EXPECT(is_palindrome_perm("aaa"));
  EXPECT(is_palindrome_perm("baa"));
  EXPECT(is_palindrome_perm("aabb"));
  EXPECT(is_palindrome_perm("ababc"));
  EXPECT(!is_palindrome_perm("abc"));
  EXPECT(!is_palindrome_perm("aabc"));
  return testing::summary();
}
