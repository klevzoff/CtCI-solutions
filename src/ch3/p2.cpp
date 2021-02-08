#include <stack>
#include <vector>
#include <cassert>

template <typename T>
class MinStack
{
public:

  MinStack() = default;

  void push(T const & val)
  {
    m_values.push(val);
    if (m_mins.empty() || val <= m_mins.top())
    {
      m_mins.push(val);
    }
  }

  [[nodiscard]]
  T const & peek() const
  {
    assert(!empty());
    return m_values.top();
  }

  [[nodiscard]]
  T const & min() const
  {
    assert(!empty());
    return m_mins.top();
  }

  void pop()
  {
    assert(!empty());
    if (m_values.top() == m_mins.top())
    {
      m_mins.pop();
    }
    m_values.pop();
  }

  [[nodiscard]]
  bool empty() const
  {
    return m_values.empty();
  }

  [[nodiscard]]
  size_t size() const
  {
    return m_values.size();
  }

private:

  std::stack<T, std::vector<T>> m_values;
  std::stack<T, std::vector<T>> m_mins;
};

int main()
{
  MinStack<int> s;
  assert(s.empty());
  s.push(5);
  assert(!s.empty());
  assert(s.size() == 1);
  assert(s.peek() == 5);
  assert(s.min() == 5);
  s.push(3);
  assert(s.size() == 2);
  assert(s.peek() == 3);
  assert(s.min() == 3);
  s.push(9);
  assert(s.size() == 3);
  assert(s.peek() == 9);
  assert(s.min() == 3);
  s.pop();
  assert(s.size() == 2);
  assert(s.peek() == 3);
  assert(s.min() == 3);
  s.pop();
  assert(s.size() == 1);
  assert(s.peek() == 5);
  assert(s.min() == 5);
  s.pop();
  assert(s.empty());
}
