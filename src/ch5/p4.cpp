#include "testing.hpp"
#include "printing.hpp"

#include <cstdint>
#include <cassert>
#include <limits>

/**
 * @brief Next number.
 *
 * Given a number, return the next integer with the same number of 1 bits in binary.
 */
std::uint32_t next_number(std::uint32_t const n)
{
  assert(n > 0);
  assert(n < std::numeric_limits<std::uint32_t>::max());
  int i = 0, ones = 0;
  for (; i < 32 && !(n & (1u << i)); ++i); // find first 1
  for (; i < 32 && n & (1u << i); ++i, ++ones); // find following 0 and count 1s in between
  // Take all bits of n above i, plus 1 at i, plus lower 1s (one fewer) shifted all the way down
  return (n & ((1ull << 32) - (1u << i))) | (1u << i) | ((1u << (ones-1)) - 1);
}

/**
 * @brief Next number.
 *
 * Given a number, return the previous integer with the same number of 1 bits in binary.
 */
std::uint32_t prev_number(std::uint32_t const n)
{
  assert(n > 0);
  assert(n < std::numeric_limits<std::uint32_t>::max());
  int i = 0, zeros = 0;
  for (; i < 32 && (n & (1u << i)); ++i); // find first 0
  for (; i < 32 && !(n & (1u << i)); ++i, ++zeros); // find following 1 and count 0s in between
  // Take all bits of n above i, plus 0 at i, plus lower 1s (one more) shifted all the way up to i-1
  return (n & ((1ull << 32) - (1u << (i+1)))) | ((1u << i) - (1u << (zeros-1)));
}

int main()
{
  EXPECT_EQ(next_number(0b01u), 0b10u);
  EXPECT_EQ(next_number(0b010u), 0b100u);
  EXPECT_EQ(next_number(0b010000u), 0b100000u);
  EXPECT_EQ(next_number(0b011u), 0b101u);
  EXPECT_EQ(next_number(0b101u), 0b110u);
  EXPECT_EQ(next_number(0b0110u), 0b1001u);
  EXPECT_EQ(next_number(0b111101110u), 0b111110011u);

  EXPECT_EQ(prev_number(0b10u), 0b01u);
  EXPECT_EQ(prev_number(0b100u), 0b010u);
  EXPECT_EQ(prev_number(0b100000u), 0b010000u);
  EXPECT_EQ(prev_number(0b101u), 0b011u);
  EXPECT_EQ(prev_number(0b110u), 0b101u);
  EXPECT_EQ(prev_number(0b1001u), 0b0110u);
  EXPECT_EQ(prev_number(0b111110011u), 0b111101110u);
  return testing::summary();
}
