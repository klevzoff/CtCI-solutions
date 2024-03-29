#include "testing.hpp"

#include <string>
#include <cassert>

/**
 * @brief Binary to string.
 *
 * Given a real number between 0 and 1, return the binary representation.
 * If the number cannot be represented exactly in 32 bits, return "ERROR".
 */
std::string to_binary_string(double v)
{
  assert(0.0 <= v && v < 1.0);
  std::string s;
  for (unsigned i = 0; i < 32 && v > 0.0; ++i)
  {
    v *= 2;
    s.push_back(static_cast<char>('0' + (v >= 1.0)));
    if (v >= 1.0)
    {
      v -= 1.0;
    }
  }
  if (v > 0.0)
  {
    return "ERROR";
  }
  s.resize(32, '0');
  return s;
}

int main()
{
  EXPECT_EQ(to_binary_string(0.0), "00000000000000000000000000000000");
  EXPECT_EQ(to_binary_string(0.5), "10000000000000000000000000000000");
  EXPECT_EQ(to_binary_string(0.25), "01000000000000000000000000000000");
  EXPECT_EQ(to_binary_string(0.75), "11000000000000000000000000000000");
  EXPECT_EQ(to_binary_string(0.875), "11100000000000000000000000000000");
  EXPECT_EQ(to_binary_string(1.0/(1u << 31)), "00000000000000000000000000000010");
  EXPECT_EQ(to_binary_string(1.0/(1ul << 32)), "00000000000000000000000000000001");
  EXPECT_EQ(to_binary_string(1.0/(1ul << 33)), "ERROR");
  EXPECT_EQ(to_binary_string(0.3), "ERROR");
  return testing::summary();
}
