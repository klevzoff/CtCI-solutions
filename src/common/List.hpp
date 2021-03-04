#ifndef CTCI_SOLUTIONS_LIST_HPP
#define CTCI_SOLUTIONS_LIST_HPP

#include <initializer_list>
#include <ostream>
#include <cassert>

/**
 * @brief Doubly-linked list
 *
 * An extremely simplified doubly-linked list data structure
 * that facilitates construction, destruction and comparison,
 * but otherwise provides no functionality and requires manual
 * pointer manipulation. Suited to interview practice problems.
 */
template <typename T>
struct List
{
  struct Node
  {
    Node * prev{};
    Node * next{};
    T val{};
  };

  Node * head{};
  Node * tail{};

  List() = default;

  List(std::initializer_list<T> const & in)
  {
    Node * prev = nullptr; 
    for (auto const & v : in)
    {
      Node * curr = new Node();
      curr->val = v;
      if (prev)
      {
        prev->next = curr;
        curr->prev = prev;
      }
      if (!head) head = curr;
      prev = curr;
    }
    tail = prev;
  }

  List(List const & other)
  {
    if (this == &other) return;
    Node * prev = nullptr; 
    for (Node * n = other.head; n != nullptr; n = n->next)
    {
      Node * curr = new Node();
      curr->val = n->val;
      if (prev)
      {
        prev->next = curr;
        curr->prev = prev;
      }
      if (!head) head = curr;
      prev = curr;
    }
    tail = prev;
  }

  List(List && other)
  {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }

  bool operator==(List const & other)
  {
    Node * lnode = head;
    Node * rnode = other.head;
    while (lnode && rnode)
    {
      if (lnode->val != rnode->val) return false;
      lnode = lnode->next;
      rnode = rnode->next;
    }
    return !lnode && !rnode;
  }

  ~List()
  {
    while (head)
    {
      Node * curr = head;
      head = curr->next;
      delete curr;
    }
  }

  [[nodiscard]]
  bool empty() const
  {
    return head == nullptr;
  }

  void add_head(T val)
  {
    auto * const node = new Node();
    node->val = std::move(val);
    node->next = head;
    if (!tail) tail = node;
    if (head) head->prev = node;
    head = node;
  }

  void rem_head()
  {
    assert(head);
    Node * tmp = head;
    if (tail == head) tail = nullptr;
    head = head->next;
    if (head) head->prev = nullptr;
    delete tmp;
  }

  void add_tail(T val)
  {
    auto * const node = new Node();
    node->val = std::move(val);
    node->prev = tail;
    if (!head) head = node;
    if (tail) tail->next = node;
    tail = node;
  }

  void rem_tail()
  {
    assert(tail);
    Node * tmp = tail;
    if (head == tail) head = nullptr;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    delete tmp;
  }

  void rem(Node * node)
  {
    if (node == head) rem_head();
    else if (node == tail) rem_tail();
    else
    {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
    }
  }

  friend std::ostream & operator<<(std::ostream & os, List<T> const & l)
  {
    Node * curr = l.head;
    os << "head -> ";
    while (curr != l.tail)
    {
      os << curr->val << " <-> ";
      curr = curr->next;
    }
    if (curr) os << curr->val;
    os << " <- tail";
    return os;
  }
};

#endif // CTCI_SOLUTIONS_LIST_HPP
