#include <stack>
#include <vector>
#include <cassert>

template <typename T>
class SetOfStacks
{
public:

  explicit SetOfStacks(size_t max_size) : m_max_size(max_size), m_stacks{} {};

  [[nodiscard]]
  bool empty() const
  {
    return m_stacks.empty();
  }

  void push(T const & val)
  {
    if (m_stacks.empty() || m_stacks.back().size() == m_max_size)
    {
      m_stacks.emplace_back();
    }
    m_stacks.back().push(val);
  }

  void pop()
  {
    assert(!empty());
    m_stacks.back().pop();
    if (m_stacks.back().empty())
    {
      m_stacks.erase(m_stacks.end()-1);
    }
  }

  [[nodiscard]]
  T const & peek() const
  {
    assert(!empty());
    return m_stacks.back().top();
  }

  [[nodiscard]]
  size_t size() const
  {
    size_t sz = 0;
    for (auto const & s : m_stacks)
    {
      sz += s.size();
    }
    return sz;
  }

  void pop_at(size_t index)
  {
    assert(index < m_stacks.size());
    assert(!m_stacks[index].empty());
    m_stacks[index].pop();
    if (m_stacks[index].empty())
    {
      m_stacks.erase(m_stacks.begin() + index);
    }
  }

private:

  size_t m_max_size;
  std::vector<std::stack<T, std::vector<T>>> m_stacks;

};

int main()
{
  SetOfStacks<int> s(3);
  assert(s.empty());
  s.push(1);
  assert(!s.empty());
  assert(s.size() == 1);
  assert(s.peek() == 1);
  s.push(2);
  s.push(3);
  assert(s.size() == 3);
  assert(s.peek() == 3);
  s.push(4);
  s.push(5);
  assert(s.size() == 5);
  assert(s.peek() == 5);
  s.pop();
  assert(s.size() == 4);
  assert(s.peek() == 4);
  s.pop_at(0);
  assert(s.size() == 3);
  assert(s.peek() == 4);
  s.pop_at(1);
  assert(s.size() == 2);
  assert(s.peek() == 2);
  s.pop();
  assert(s.size() == 1);
  assert(s.peek() == 1);
  s.pop_at(0);
  assert(s.empty());
}
