#include "testing.hpp"

#include <string>
#include <algorithm>
#include <cassert>

/**
 * @brief URLify.
 *
 * Replace all spaces in a string with '%20'. Assume the string has sufficient space at the end.
 * True length of the string given as input.
 * Time complexity: O(N).
 * Space complexity: O(1).
 */
void urlify(std::string & s, size_t const len)
{
  size_t num_space = 0;
  for (size_t i = 0; i < len; ++i)
    if (s[i] == ' ')
      ++num_space;

  auto rit = begin(s) + len - 1;
  auto wit = begin(s) + len + 2 * num_space - 1;

  do
  {
    if (*rit != ' ')
    {
      *wit-- = *rit--;
    }
    else
    {
      *wit-- = '0';
      *wit-- = '2';
      *wit-- = '%';
      --rit;
    }
  } while (rit != wit);
}

void test(std::string s, std::string const & e)
{
  size_t const len = s.length();
  size_t const num_space = count(begin(s), end(s), ' ');
  s.resize(len + 2 * num_space, ' ');
  urlify(s, len);
  EXPECT_EQ(s, e);
}

int main()
{
  test("", "");
  test("a", "a");
  test("a b", "a%20b");
  test("a ", "a%20");
  test("Mr John Smith", "Mr%20John%20Smith");
  test(" a b", "%20a%20b");
  return testing::summary();
}
