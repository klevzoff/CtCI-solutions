#include "testing.hpp"

#include <cstdint>
#include <algorithm>

/**
 * @brief Flip bit to win.
 *
 * Find length of the longest sequence of 1s created by flipping a single bit.
 */
unsigned longest_bitseq_flip(std::uint32_t n)
{
  unsigned prev = 0;
  unsigned curr = 0;
  unsigned max_seq = 1;
  for (; n; n >>= 1)
  {
    if (n & 1u)
    {
      ++curr;
    }
    else
    {
      max_seq = std::max(max_seq, prev + curr + 1);
      prev = curr;
      curr = 0;
    }
  }
  return max_seq;
}

int main()
{
  EXPECT_EQ(longest_bitseq_flip(0b0u), 1u);
  EXPECT_EQ(longest_bitseq_flip(0b1010101010101u), 3u);
  EXPECT_EQ(longest_bitseq_flip(0b111001110111u), 7u);
  EXPECT_EQ(longest_bitseq_flip(0b11011101111u), 8u);
  EXPECT_EQ(longest_bitseq_flip(0b11100111u), 4u);
  return testing::summary();
}
