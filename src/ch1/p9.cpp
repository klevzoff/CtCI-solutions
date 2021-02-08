#include <string>
#include <cassert>

bool is_substring(std::string const & s1, std::string const & s2)
{
  return s2.find(s1) != std::string::npos;
}

/**
 * @brief String Rotation.
 *
 * Assume function is_substring() is available.
 * Check if one string is a rotation of the other using only one call to is_substring().
 * Time complexity: O(s2.size()) (+ whatever is_substring() requires).
 * Space complexity: O(s2.size()) (+ whatever is_substring() requires).
 */
bool is_rotation(std::string const & s1, std::string const & s2)
{
  return s1.size() == s2.size() && is_substring(s1, s2+s2);
}

int main()
{
  assert(is_rotation("", ""));
  assert(is_rotation("a", "a"));
  assert(is_rotation("ab", "ba"));
  assert(is_rotation("abba", "baab"));
  assert(is_rotation("aabb", "baab"));
  assert(!is_rotation("a", "b"));
  assert(!is_rotation("aabb", "baba"));
}
