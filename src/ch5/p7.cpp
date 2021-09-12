#include "testing.hpp"

#include <cstdint>

/**
 * @brief Pairwise swap.
 *
 * Swap odd and even bits of a number in as few instructions as possible.
 */
std::uint32_t pairwise_bit_swap(std::uint32_t const n)
{
  constexpr std::uint32_t odd = 0b10101010101010101010101010101010u;
  return ((n & odd) >> 1) | ((n & ~odd) << 1);
}

int main()
{
  EXPECT_EQ(pairwise_bit_swap(0b0u), 0b0u);
  EXPECT_EQ(pairwise_bit_swap(0b01u), 0b10u);
  EXPECT_EQ(pairwise_bit_swap(0b10u), 0b01u);
  EXPECT_EQ(pairwise_bit_swap(0b110011u), 0b110011u);
  EXPECT_EQ(pairwise_bit_swap(0b11001u), 0b100110u);
  EXPECT_EQ(pairwise_bit_swap(0b10101010101010101010101010101010u), 0b01010101010101010101010101010101u);
  return testing::summary();
}
