#include "testing.hpp"

#include <string>

/**
 * @brief Is Unique
 *
 * Determine if a string has all unique characters.
 * Time complexity: O(N).
 * Space complexity: O(1) (since fixed character set).
 */
bool all_unique_chars(std::string const & s)
{
  bool flag[256]{false};
  for (char c : s)
  {
    int const v = static_cast<unsigned char>(c);
    if (flag[v]) return false;
    flag[v] = true;
  }
  return true;
}

int main()
{
  EXPECT(all_unique_chars(""));
  EXPECT(all_unique_chars("a"));
  EXPECT(all_unique_chars("abc"));
  EXPECT(!all_unique_chars("aa"));
  EXPECT(!all_unique_chars("abcdefgb"));
  return testing::summary();
}
