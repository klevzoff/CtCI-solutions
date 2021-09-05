#include "testing.hpp"

#include <string>
#include <charconv>

/**
 * @brief String Compression.
 *
 * Given an input string, return a basic compression of the string using consecutive character counts.
 * If the compressed string is not shorter, return the input string.
 * Time complexity: O(N).
 * Space complexity: O(1) (not including space for result).
 */
std::string compress(std::string const & s)
{
  if (s.empty()) return s;
  std::string r(s.size(), ' ');
  char * pos = r.data();
  size_t cnt = 1;

  for (size_t i = 1; i < s.size()+1; ++i)
  {
    if (i < s.size() && s[i] == s[i-1])
    {
      ++cnt;
    }
    else
    {
      *pos++ = s[i-1];
      auto res = std::to_chars(pos, r.data() + r.size() - 1, cnt);
      if (res.ec == std::errc::value_too_large) return s;
      pos = res.ptr;
      cnt = 1;
    }
  }
  r.resize(pos - r.data());
  return r;
}

int main()
{
  EXPECT_EQ(compress(""), "");
  EXPECT_EQ(compress("a"), "a");
  EXPECT_EQ(compress("aa"), "aa");
  EXPECT_EQ(compress("aaa"), "a3");
  EXPECT_EQ(compress("aabb"), "aabb");
  EXPECT_EQ(compress("aaabb"), "a3b2");
  EXPECT_EQ(compress("aabcccccaaa"), "a2b1c5a3");
  return testing::summary();
}
