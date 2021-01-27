#include <string>
#include <cassert>

using namespace std;

/**
 * @brief Is Unique
 *
 * Determine if a string has all unique characters.
 */
bool all_unique_chars(string const & s)
{
  bool flag[256]{false};
  for (char c : s)
  {
    int const v = static_cast<unsigned char>(c);
    if (flag[v]) return false;
    flag[v] = true;
  }
  return true;
}

int main()
{
  assert(all_unique_chars(""));
  assert(all_unique_chars("a"));
  assert(all_unique_chars("abc"));
  assert(!all_unique_chars("aa"));
  assert(!all_unique_chars("abcdefgb"));
}
