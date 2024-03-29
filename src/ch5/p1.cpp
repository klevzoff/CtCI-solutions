#include "testing.hpp"

#include <cstdint>
#include <cassert>

/**
 * @brief Insertion.
 *
 * Insert low bits of @src into positions [i,j] of @dst.
 * @pre 0 <= i <= j < 32
 */
std::uint32_t insert_bits(std::uint32_t const dst,
                          std::uint32_t const src,
                          unsigned const i,
                          unsigned const j )
{
  assert(i <= j && j < 32);
  std::uint32_t const dst_mask = (1u << (j + 1)) - (1u << i);
  std::uint32_t const src_mask = (1u << (j + 1)) - 1;
  return (dst & ~dst_mask) | (src & src_mask) << i;
}

int main()
{
  EXPECT_EQ(insert_bits(0b01u, 0b10, 1, 2), 0b101u);
  EXPECT_EQ(insert_bits(0b0u, 0b101011, 5, 10), 0b10101100000u);
  EXPECT_EQ(insert_bits(0b10101100000u, 0b101011u, 5, 10), 0b10101100000u);
  EXPECT_EQ(insert_bits(0b10000000000u, 0b10011u, 2, 6), 0b10001001100u);
  return testing::summary();
}
