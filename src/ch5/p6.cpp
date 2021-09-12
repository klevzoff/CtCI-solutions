#include "testing.hpp"

#include <cstdint>

/**
 * @brief Conversion.
 *
 * Determine the number of bits to flip to convert a into b.
 */
unsigned num_bits_to_convert(std::uint32_t const a, std::uint32_t const b)
{
  std::uint32_t c = a ^ b;
  unsigned n = 0;
  while (c)
  {
    c = c & (c-1);
    ++n;
  }
  return n;
}

int main()
{
  EXPECT_EQ(num_bits_to_convert(0b0u, 0b0u), 0u);
  EXPECT_EQ(num_bits_to_convert(0b1u, 0b1u), 0u);
  EXPECT_EQ(num_bits_to_convert(0b110101101u, 0b110101101u), 0u);
  EXPECT_EQ(num_bits_to_convert(0b110101101u, 0b110101111u), 1u);
  EXPECT_EQ(num_bits_to_convert(0b110101111u, 0b110101101u), 1u);
  EXPECT_EQ(num_bits_to_convert(0b111101101u, 0b110101100u), 2u);
  EXPECT_EQ(num_bits_to_convert(0b0u, 0b11111111u), 8u);
  EXPECT_EQ(num_bits_to_convert((1u<<31)-1, (1u<<7)-1), 24u);
  return testing::summary();
}
