#include <stack>
#include <vector>
#include <cassert>

template <typename T>
class MyQueue
{
public:

  MyQueue() : m_rem_stack{}, m_add_stack{}, m_adding{true} { };

  void add(T const & val)
  {
    if (!m_adding)
    {
      reverse_stack(m_rem_stack, m_add_stack);
      m_adding = true;
    }
    m_add_stack.push(val);
  }

  void remove()
  {
    assert(!empty());
    if (m_adding)
    {
      reverse_stack(m_add_stack, m_rem_stack);
      m_adding = false;
    }
    m_rem_stack.pop();
  }

  [[nodiscard]]
  T const & peek() const
  {
    assert(!empty());
    if (m_adding)
    {
      reverse_stack(m_add_stack, m_rem_stack);
      m_adding = false;
    }
    return m_rem_stack.top();
  }

  [[nodiscard]]
  bool empty() const
  {
    return m_adding ? m_add_stack.empty() : m_rem_stack.empty();
  }

private:

  using stack_type = std::stack<T, std::vector<T>>;

  static void reverse_stack(stack_type & src, stack_type & dst)
  {
    while (!src.empty())
    {
      dst.emplace(std::move(src.top()));
      src.pop();
    }
  }

  mutable stack_type m_rem_stack;
  mutable stack_type m_add_stack;
  mutable bool m_adding;

};

int main()
{
  MyQueue<int> q;
  assert(q.empty());
  q.add(1);
  assert(!q.empty());
  assert(q.peek() == 1);
  q.add(2);
  assert(!q.empty());
  assert(q.peek() == 1);
  q.remove();
  assert(!q.empty());
  assert(q.peek() == 2);
  q.remove();
  assert(q.empty());
}
