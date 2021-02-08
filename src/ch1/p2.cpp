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
  assert(is_permutation("", ""));
  assert(is_permutation("a", "a"));
  assert(is_permutation("ab", "ba"));
  assert(is_permutation("abcde", "dbace"));
  assert(!is_permutation("", "a"));
  assert(!is_permutation("a", "b"));
  assert(!is_permutation("abcde", "dbacf"));
}
