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
void urlify(std::string & s, size_t len)
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

bool test(std::string s, std::string const & e)
{
  size_t const len = s.length();
  size_t const num_space = count(begin(s), end(s), ' ');
  s.resize(len + 2 * num_space, ' ');
  urlify(s, len);
  return s == e;
}

int main()
{
  assert(test("", ""));
  assert(test("a", "a"));
  assert(test("a b", "a%20b"));
  assert(test("a ", "a%20"));
  assert(test("Mr John Smith", "Mr%20John%20Smith"));
  assert(test(" a b", "%20a%20b"));
}
