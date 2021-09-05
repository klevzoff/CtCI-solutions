#include "testing.hpp"

#include <string>
#include <cassert>
#include <algorithm>

/**
 * @brief Check Permutation
 *
 * Given two strings, decide if one is permutation of the other.
 * Time complexity: O(N).
 * Space complexity: O(1) (since fixed character set).
 */
bool is_permutation(std::string const & s1, std::string const & s2)
{
  if (s1.size() != s2.size()) return false;
  int cnt[256]{};
  for (char c : s1) ++cnt[static_cast<unsigned char>(c)];
  for (char c : s2) --cnt[static_cast<unsigned char>(c)];
  return std::all_of(std::begin(cnt), std::end(cnt), [](int v){ return v == 0; });
}

int main()
{
  EXPECT(is_permutation("", ""));
  EXPECT(is_permutation("a", "a"));
  EXPECT(is_permutation("ab", "ba"));
  EXPECT(is_permutation("abcde", "dbace"));
  EXPECT(!is_permutation("", "a"));
  EXPECT(!is_permutation("a", "b"));
  EXPECT(!is_permutation("abcde", "dbacf"));
  return testing::summary();
}
