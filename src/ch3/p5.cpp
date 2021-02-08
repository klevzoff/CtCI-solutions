#include <stack>
#include <vector>
#include <cassert>
#include <algorithm>

template <typename T, template <typename U> typename Container>
void reverse_stack(std::stack<T, Container<T>> & src,
                   std::stack<T, Container<T>> & dst)
{
  while (!src.empty())
  {
    dst.emplace(std::move(src.top()));
    src.pop();
  }
}

template <typename T, template <typename U> class Container>
void sort_stack(std::stack<T, Container<T>> & s)
{
  std::stack<T, Container<T>> aux;
  auto num_vals = 0;

  // count number of elements and find the smallest
  while (!s.empty())
  {
    ++num_vals;
    aux.template emplace(std::move(s.top()));
    s.pop();
  }
  reverse_stack(aux, s);

  while (num_vals-- > 0)
  {
    size_t n = num_vals;
    T maxval = std::move(s.top());
    s.pop();
    // move remaining elements into aux stack but find and keep largest value separate
    while (n-- > 0)
    {
      aux.emplace(std::move(s.top()));
      s.pop();
      if (aux.top() > maxval)
      {
        using std::swap;
        swap(maxval, aux.top());
      }
    }
    // push largest of remaining elements back into s
    s.emplace(std::move(maxval));
    // move values back from aux into s
    reverse_stack(aux, s);
  }
}

void test(std::vector<int> input)
{
  std::stack<int, std::vector<int>> s(input);
  sort_stack(s);
  std::sort(begin(input), end(input));
  for (auto v : input)
  {
    assert(!s.empty());
    assert(s.top() == v);
    s.pop();
  }
  assert(s.empty());
}

int main()
{
  test({1,2,3,4,5});
  test({5,3,1,4,2});
  test({5,4,3,2,1});
}
