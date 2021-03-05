#ifndef CTCI_SOLUTIONS_FWDLIST_HPP
#define CTCI_SOLUTIONS_FWDLIST_HPP

#include <initializer_list>
#include <ostream>

/**
 * @brief Singly-linked list
 *
 * An extremely simplified singly-linked list data structure
 * that facilitates construction, destruction and comparison,
 * but otherwise provides no functionality and requires manual
 * pointer manipulation. Suited to interview practice problems.
 */
template <typename T>
struct FwdList
{
  struct Node
  {
    Node * next{};
    T val{};
  };

  Node * head{};

  FwdList() = default;

  explicit FwdList(Node * h) : head(h) {}

  FwdList(std::initializer_list<T> const & in)
  {
    Node * prev = nullptr; 
    for (auto const & v : in)
    {
      Node * curr = new Node();
      curr->val = v;
      if (prev)
      {
        prev->next = curr;
      }
      if (!head) head = curr;
      prev = curr;
    }
  }

  FwdList(FwdList const & other)
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
      }
      if (!head) head = curr;
      prev = curr;
    }
  }

  FwdList(FwdList && other)
  {
    std::swap(head, other.head);
  }

  bool operator==(FwdList const & other) const
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

  ~FwdList()
  {
    while (head)
    {
      Node * curr = head;
      head = curr->next;
      delete curr;
    }
  }

  friend std::ostream & operator<<(std::ostream & os, FwdList<T> const & l)
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

#endif // CTCI_SOLUTIONS_FWDLIST_HPP
