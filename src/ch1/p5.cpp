#include "testing.hpp"

#include <string>

/**
 * @brief One Away.
 *
 * Check if two string are at most one edit away from each other.
 * Time complexity: O(min(N1, N2)).
 * Space complexity: O(1).
 */
bool one_away(std::string const & s1, std::string const & s2)
{
  int const len_diff = static_cast<int>(size(s1)) - static_cast<int>(size(s2));
  if (abs(len_diff) > 1)
    return false;

  size_t num_diff = 0;
  for (size_t i = 0, j = 0; i < size(s1) && j < size(s2);)
  {
    if (s1[i] != s2[j])
    {
      if (num_diff > 0) return false;
      ++num_diff;
      if (len_diff >= 0) ++i;
      if (len_diff <= 0) ++j;
    }
    else
    {
      ++i;
      ++j;
    }
  }
  return true;
}

int main()
{
  EXPECT(one_away("", ""));
  EXPECT(one_away("a", "a"));
  EXPECT(one_away("a", "b"));
  EXPECT(one_away("a", "ab"));
  EXPECT(one_away("ab", "a"));
  EXPECT(one_away("ab", "ac"));
  EXPECT(!one_away("", "ab"));
  EXPECT(!one_away("ab", "cd"));
  EXPECT(!one_away("abcde", "acdef"));
  return testing::summary();
}
