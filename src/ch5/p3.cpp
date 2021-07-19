#include <cstdint>
#include <cassert>
#include <algorithm>

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
  assert(longest_bitseq_flip(0b0) == 1);
  assert(longest_bitseq_flip(0b1010101010101) == 3);
  assert(longest_bitseq_flip(0b111001110111) == 7);
  assert(longest_bitseq_flip(0b11011101111) == 8);
  assert(longest_bitseq_flip(0b11100111) == 4);
}
