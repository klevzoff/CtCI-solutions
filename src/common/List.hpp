#include <initializer_list>
#include <iostream>

/**
 * @brief Doubly-linked list
 *
 * An extremely simplified doubly-linked list data structure
 * that facilitates construction, destruction and comparison,
 * but otherwise provides no functionality and requires manual
 * pointer manipulation. Suited to interview practice problems.
 */
template<typename T>
struct List
{
  struct Node
  {
    Node * prev{};
    Node * next{};
    T val{};
  };

  Node * head{};

  List() {}

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
  }

  List(List && other) = default;

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

  friend std::ostream & operator<<(std::ostream & os, List<T> const & l)
  {
    Node * curr = l.head;
    os << "head -> ";
    while (curr)
    {
      os << curr->val << " <-> ";
      curr = curr->next;
    }
    os << "null";
    return os;
  }
};
