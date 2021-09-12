#include "testing.hpp"
#include "printing.hpp"

#include <cstdint>
#include <utility>

/**
 * @brief Next number.
 *
 * Given a number, return the next smallest and next largest integers
 * with the same number of 1 bits in their binary representation.
 */
std::pair<std::uint32_t, std::uint32_t> next_number(std::uint32_t n)
{
  // smallest next number with same number of 1s is obtained by shifting
  // highest 1 bit in the lowest 1-bit sequence up one position, which is
  // equivalent to adding the corresponding power of 2.
  int i;
  for (i = 0; i < 32 && !(n & (1u << i)); ++i); // find first 1
  for (; i < 32 && n & (1u << i); ++i); // find following 0
  std::uint32_t const m = n + (1u << (i-1));

  // largest next number with same number of 1s is just sum of the highest bits
  std::uint32_t M = 0;
  int j = 32;
  while (n != 0)
  {
    n &= n - 1;
    M |= 1u << --j;
  }

  return {m, M};
}

int main()
{
  EXPECT_EQ(next_number(0b1u), std::make_pair(0b10u, 0b10000000000000000000000000000000u));
  EXPECT_EQ(next_number(0b10u), std::make_pair(0b100u, 0b10000000000000000000000000000000u));
  EXPECT_EQ(next_number(0b10000u), std::make_pair(0b100000u, 0b10000000000000000000000000000000u));
  EXPECT_EQ(next_number(0b11u), std::make_pair(0b101u, 0b11000000000000000000000000000000u));
  EXPECT_EQ(next_number(0b101u), std::make_pair(0b110u, 0b11000000000000000000000000000000u));
  EXPECT_EQ(next_number(0b110u), std::make_pair(0b1010u, 0b11000000000000000000000000000000u));
  EXPECT_EQ(next_number(0b111101110u), std::make_pair(0b111110110u, 0b11111110000000000000000000000000u));
  return testing::summary();
}
