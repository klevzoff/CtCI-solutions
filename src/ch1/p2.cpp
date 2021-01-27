#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

bool is_permutation(string const & s1, string const & s2)
{
  if (s1.size() != s2.size()) return false;
  int cnt[256]{};
  for (char c : s1) ++cnt[static_cast<unsigned char>(c)];
  for (char c : s2) --cnt[static_cast<unsigned char>(c)];
  return all_of(begin(cnt), end(cnt), [](int v){ return v == 0; });
}

int main()
{
  assert(is_permutation("", ""));
  assert(is_permutation("a", "a"));
  assert(is_permutation("ab", "ba"));
  assert(is_permutation("abcde", "dbace"));
  assert(!is_permutation("", "a"));
  assert(!is_permutation("a", "b"));
  assert(!is_permutation("abcde", "dbacf"));
}
