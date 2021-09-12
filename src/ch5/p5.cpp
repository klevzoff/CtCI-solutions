#include "testing.hpp"

#include <cstdint>

/**
 * @brief Debugger.
 *
 * Explain what the following function does.
 */
bool f(std::uint32_t const n)
{
  /*
   * Subtracting 1 from n flips its lowest 1-bit to 0 and all 0 bits below it to 1.
   * Logical and with n itself therefore leaves all bits unchanged except the lowest 1-bit
   * which becomes 0. So expression on the lhs of comparison removes lowest set bit of n.
   * The number can only become zero if it only had a single 1-bit. Therefore the function
   * checks that a number only has a single 1-bit, or in other words, is a power of 2.
   */
  return (n & (n-1)) == 0;
}

int main()
{
  return testing::summary();
}
