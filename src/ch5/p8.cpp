#include "testing.hpp"
#include "printing.hpp"

#include <cstddef>
#include <cassert>
#include <vector>
#include <algorithm>
#include <limits>

constexpr int NBIT = std::numeric_limits<unsigned char>::digits;

/// Generates a byte with bit pattern set in [lo;hi) half-open range.
std::byte bits(unsigned const lo, unsigned const hi)
{
  return static_cast<std::byte>((1 << hi) - (1 << lo));
}

/**
 * @brief Draw line.
 *
 * Given a byte buffer that represents a monochrome screen (1 byte per pixel)
 * and its width (divisible by 8), draw a horizontal line from (x1, y) to (x2, y).
 */
void draw_line(std::vector<std::byte> & screen,
               size_t const width,
               size_t const x1,
               size_t const x2,
               size_t const y)
{
  assert(width % NBIT == 0);
  assert(x1 < width && x2 < width && y < screen.size() * NBIT / width);

  auto const [xmin, xmax] = std::minmax(x1, x2);
  size_t const bmin = (y * width + xmin) / NBIT;
  size_t const bmax = (y * width + xmax) / NBIT;

  if (bmin == bmax)
  {
    screen[bmin] |= bits(xmin % NBIT, xmax % NBIT + 1);
  }
  else
  {
    screen[bmin] |= bits(xmin % NBIT, NBIT);
    for (size_t i = bmin + 1; i < bmax; ++i)
    {
      screen[i] = bits(0, NBIT);
    }
    screen[bmax] |= bits(0, xmax % NBIT + 1);
  }
}

void test(std::vector<std::byte> const & screen,
          size_t const width,
          size_t const x1,
          size_t const x2,
          size_t const y,
          std::vector<std::byte> const & expect)
{
  std::vector<std::byte> result = screen;
  draw_line(result, width, x1, x2, y);
  EXPECT_EQ(result, expect);
}

int main()
{
  // Note that we interpret low bits as being "left" on the screen and high bits as "right".
  // Therefore, each byte should be reversed compared to its textual bit representation.
  // This test suite is not very exhaustive, but I can't be bothered.

  test({std::byte{0b01001000},std::byte{0b10000000},std::byte{0b00011001}},
       8, 2, 5, 1,
       {std::byte{0b01001000},std::byte{0b10111100},std::byte{0b00011001}});

  test({std::byte{0b01001000},std::byte{0b10000000},std::byte{0b00011001}},
       8, 5, 2, 1,
       {std::byte{0b01001000},std::byte{0b10111100},std::byte{0b00011001}});

  test({std::byte{0b00000000},std::byte{0b00000000},std::byte{0b00000000}},
       24, 7, 18, 0,
       {std::byte{0b10000000},std::byte{0b11111111},std::byte{0b00000111}});

  return testing::summary();
}
