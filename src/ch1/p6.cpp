#include <string>
#include <charconv>
#include <cassert>

using namespace std;

/**
 * @brief String Compression.
 *
 * Given an input string, return a basic compression of the string using consecutive character counts.
 * If the compressed string is not shorter, return the input string.
 * Time complexity: O(N).
 * Space complexity: O(1) (not including space for result).
 */
string compress(string const & s)
{
  if (s.empty()) return s;
  string r(s.size(), ' ');
  char * pos = r.data();
  size_t cnt = 1;

  for (size_t i = 1; i < s.size()+1; ++i)
  {
    if (i < s.size() && s[i] == s[i-1])
    {
      ++cnt;
    }
    else
    {
      *pos++ = s[i-1];
      auto res = to_chars(pos, r.data() + r.size() - 1, cnt);
      if (res.ec == errc::value_too_large) return s;
      pos = res.ptr;
      cnt = 1;
    }
  }
  r.resize(pos - r.data());
  return r;
}

int main()
{
  assert(compress("") == "");
  assert(compress("a") == "a");
  assert(compress("aa") == "aa");
  assert(compress("aaa") == "a3");
  assert(compress("aabb") == "aabb");
  assert(compress("aaabb") == "a3b2");
  assert(compress("aabcccccaaa") == "a2b1c5a3");
}
