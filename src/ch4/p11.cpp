#include "Tree.hpp"

#include <cassert>
#include <cstddef>
#include <random>
#include <algorithm>

/**
 * @brief Random Node.
 *
 * Implement a binary search tree class with a random_node() function.
 * All nodes must have equal probabilities to be returned.
 * Must not impact complexity of standard tree operations (insert, remove, find).
 */
template<typename T>
class UnbalancedBinarySearchTree
{
public:

  struct Node
  {
    using value_type = T;

    T value{};
    Node * left = nullptr;
    Node * right = nullptr;
    size_t lsize = 0;
    size_t rsize = 0;
  };

  UnbalancedBinarySearchTree() = default;

  ~UnbalancedBinarySearchTree()
  {
    tree_ops::erase(root);
  }

  Node * insert(T val)
  {
    Node * node = root;
    Node * parent = nullptr;
    while (node)
    {
      parent = node;
      if (val <= node->value)
      {
        ++node->lsize;
        node = node->left;
      }
      else
      {
        ++node->rsize;
        node = node->right;
      }
    }
    node = new Node;
    node->value = val;
    if (parent)
    {
      if (val <= parent->value) parent->left = node;
      else parent->right = node;
    }
    else
    {
      root = node;
    }
    return node;
  }

  void remove(T const & val)
  {
    Node * node = root;
    Node * parent = nullptr;
    while (node && node->value != val)
    {
      parent = node;
      if (val <= node->value)
      {
        --node->lsize;
        node = node->left;
      }
      else
      {
        --node->rsize;
        node = node->right;
      }
    }
    assert(node); // do not allow removing non-existent values, makes things easier
    if (!node->left || !node->right) // easy case
    {
      Node * const child = node->left ? node->left : node->right;
      if (parent)
      {
        if (node == parent->left) parent->left = child;
        else parent->right = child;
      }
      else
      {
        root = child;
      }
    }
    else
    {
      // find successor
      Node * succ = node->right;
      Node * succ_parent = node;
      while (succ->left)
      {
        succ_parent = succ;
        succ = succ->left;
      }
      // replace current node with successor
      succ->left = node->left;
      if (succ != node->right) succ->right = node->right;
      succ->lsize = node->lsize;
      succ->rsize = node->rsize-1;
      succ_parent->left = nullptr;
      if (parent)
      {
        if (node == parent->left) parent->left = succ;
        else parent->right = succ;
      }
      else
      {
        root = succ;
      }
    }
    delete node;
  }

  [[nodiscard]]
  Node const * find(T const & val) const
  {
    Node const * node = root;
    while (node && node->value != val)
    {
      if (val <= node->value) node = node->left;
      else node = node->right;
    }
    return node;
  }

  [[nodiscard]]
  Node * find(T const & val)
  {
    return const_cast<Node *>(const_cast<UnbalancedBinarySearchTree const *>(this)->find(val));
  }

  [[nodiscard]]
  Node const * random_node() const
  {
    static std::mt19937 rng(2021);
    Node const * node = root;
    while (node)
    {
      std::uniform_int_distribution<> distrib(-node->lsize, node->rsize);
      int const choice = distrib(rng);
      if (choice == 0) return node;
      else if (choice < 0) node = node->left;
      else node = node->right;
    }
    return nullptr; // this should never happen (unless tree is empty)
  }

  [[nodiscard]]
  Node * random_node()
  {
    return const_cast<Node *>(const_cast<UnbalancedBinarySearchTree const *>(this)->random_node());
  }

private:

  Node * root = nullptr;
};

/**
 * This test is based on the assumption that given enough attempts,
 * every node will come up at least once, regardless of platform.
 * It does not, however, check that frequencies are indeed equal.
 * Nor does if properly test insert, find and remove functions.
 * Also, it doesn't work with repeated input values;
 */
bool test(std::vector<int> const & input)
{
  UnbalancedBinarySearchTree<int> tree;
  for (int v : input)
    tree.insert(v);
  std::vector<int> counts(input.size());
  for (size_t i = 0; i < input.size() * 100; ++i)
  {
    UnbalancedBinarySearchTree<int>::Node const * const node = tree.random_node();
    if (!node) return false;
    auto it = std::find(begin(input), end(input), node->value);
    if (it == end(input)) return false;
    ++counts[std::distance(begin(input), it)];
  }
  for (int v : input)
    tree.remove(v);
  return std::all_of(begin(counts), end(counts), [](int v){ return v > 0; });
}

int main()
{
  assert(test({0}));
  assert(test({0,1}));
  assert(test({1,0}));
  assert(test({1,2,0}));
  assert(test({1,0,2}));
  assert(test({4,2,5,1,3,8,7}));
}
