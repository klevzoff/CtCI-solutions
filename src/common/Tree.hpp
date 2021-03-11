#ifndef CTCI_SOLUTIONS_TREE_HPP
#define CTCI_SOLUTIONS_TREE_HPP

#include <ostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <initializer_list>

namespace tree_ops
{

template<typename Node, typename Comp>
static bool compare(Node const * a, Node const * const b, Comp comp)
{
  if (a == b) return true;    // same node trivial case
  if (!a != !b) return false; // both null or non-null
  return comp(a->value, b->value)
         && compare(a->left, b->left, comp)
         && compare(a->right, b->right, comp);
}

template<typename Node>
static void print(std::ostream & os, Node const * const node, int level)
{
  os << std::string(level * 2, ' ') << "-> ";
  if (!node)
  {
    os << "null\n";
  }
  else
  {
    os << node->value << "\n";
    print(os, node->left, level + 1);
    print(os, node->right, level + 1);
  }
}

template<typename Node>
static void erase(Node * const node)
{
  if (!node) return;
  erase(node->left);
  erase(node->right);
  delete node;
}

template<typename Node>
static size_t depth(Node const * const node)
{
  if (!node) return 0;
  return 1 + std::max(depth(node->left), depth(node->right));
}

template<typename Node>
static size_t size(Node const * const node)
{
  if (!node) return 0;
  return 1 + size(node->left) + size(node->right);
}

template<typename Node>
static void values(Node const * const node, std::vector<typename Node::value_type> & vals)
{
  if (!node) return;
  values(node->left, vals);
  vals.push_back(node->value);
  values(node->right, vals);
}

/**
 * @brief Find node with a given value.
 */
template<typename Node>
Node const * find(Node const * const node, typename Node::value_type const & v)
{
  if (!node) return nullptr;
  if (node->value == v) return node;
  Node const * const res = find(node->left, v);
  if (res) return res;
  return find(node->right, v);
}

/**
 * @brief Find node with a given value assuming a binary search tree.
 */
template<typename Node>
Node const * find_bst(Node const * node, typename Node::value_type const & v)
{
  while (node && node->value != v)
  {
    if (v <= node->value) node = node->left;
    else node = node->right;
  }
  return node;
}

} // namespace tree_ops

/**
 * @brief Simple wrapper struct for a binary tree
 *
 * Main goal is to automate copying/printing/destruction of the tree.
 * Constructor from a node-tuple-list is provided to facilitate testing.
 * Normally tree construction would be performed manually in problems.
 */
template<typename T>
struct BinaryTree
{
  struct Node
  {
    using value_type = T;

    T value{};
    Node * left{};
    Node * right{};
  };

  Node * root{};

  BinaryTree() = default;

  explicit BinaryTree(Node * r) : root(r) {}

  /**
   * @brief Construct a binary tree from a list of nodes with unique integer identifiers.
   *
   * Each input element is a quadruplet {nodeID, leftID, rightID, value}.
   * Non-existent child IDs are interpreted as null pointers.
   * Turns an input like {{0,1,2,42},{1,-1,-1,43},{2,-1,-1,44}} into:
   *     42
   *   /   \
   *  43   44
   */
  BinaryTree(std::initializer_list<std::tuple<int,int,int,T>> const & nodelist)
  {
    if (nodelist.size() == 0) return;
    int const rootID = std::get<0>(*nodelist.begin());

    // turn init-list into a map for easier node lookup and removal
    std::unordered_map<int, std::tuple<int,int,T>> nodemap;
    for (auto const & t : nodelist)
    {
      int const id = std::get<0>(t);
      assert(nodemap.count(id) == 0); // check for non-repeating IDs
      nodemap[id] = std::make_tuple(std::get<1>(t), std::get<2>(t), std::get<3>(t));
    }

    root = buildTree(nodemap, rootID);
  }

  BinaryTree(BinaryTree<T> const & other)
  {
    root = copyTree(other.root);
  }

  BinaryTree(BinaryTree<T> && other) noexcept
  {
    std::swap(root, other.root);
  }

  ~BinaryTree()
  {
    tree_ops::erase(root);
  }

  bool operator==(BinaryTree<T> const & other) const
  {
    return tree_ops::compare(root, other.root, std::equal_to<>{});
  }

  friend std::ostream & operator<<(std::ostream & os, BinaryTree<T> const & l)
  {
    os << "root" << "\n";
    tree_ops::print(os, l.root, 0);
    os.flush();
    return os;
  }

  [[nodiscard]] size_t depth() const
  {
    return tree_ops::depth(root);
  }

  [[nodiscard]] size_t size() const
  {
    return tree_ops::size(root);
  }

  [[nodiscard]] std::vector<T> values() const
  {
    std::vector<T> vals;
    tree_ops::values(root, vals);
    return vals;
  }

  [[nodiscard]] Node const * find(T const & v) const
  {
    return tree_ops::find(root, v);
  }

  [[nodiscard]] Node const * find_bst(T const & v) const
  {
    return tree_ops::find_bst(root, v);
  }

  ////////////////////////////////////////////////////////////////////////////////

private:

  template<typename ID>
  static Node * buildTree(std::unordered_map<ID, std::tuple<ID,ID,T>> & nodemap, ID const & nodeID)
  {
    if (nodemap.count(nodeID) == 0) return nullptr;
    std::tuple<ID,ID,T> t = nodemap.at(nodeID);
    nodemap.erase(nodeID);
    Node * const node = new Node;
    node->value = std::get<2>(t);
    node->left  = buildTree(nodemap, std::get<0>(t));
    node->right = buildTree(nodemap, std::get<1>(t));
    return node;
  }

  static Node * copyTree(Node const * const node)
  {
    if (!node) return nullptr;
    Node * const copy = new Node;
    copy->value = node->value;
    copy->left = copyTree(node->left);
    copy->right = copyTree(node->right);
    return copy;
  }
};

/**
 * @brief Same as BinaryTree, but with parent links in each node.
 */
template<typename T>
struct BinaryPTree
{
  struct Node
  {
    using value_type = T;

    T value{};
    Node * left{};
    Node * right{};
    Node * parent{};
  };

  Node * root{};

  BinaryPTree() = default;

  explicit BinaryPTree(Node * r) : root(r) {}

  /**
   * @brief Construct a binary tree from a list of nodes with unique integer identifiers.
   *
   * Each input element is a quadruplet {nodeID, leftID, rightID, value}.
   * Non-existent child IDs are interpreted as null pointers.
   * Turns an input like {{0,1,2,42},{1,-1,-1,43},{2,-1,-1,44}} into:
   *     42
   *   /   \
   *  43   44
   */
  BinaryPTree(std::initializer_list<std::tuple<int,int,int,T>> const & nodelist)
  {
    if (nodelist.size() == 0) return;
    int const rootID = std::get<0>(*nodelist.begin());

    // turn init-list into a map for easier node lookup and removal
    std::unordered_map<int, std::tuple<int,int,T>> nodemap;
    for (auto const & t : nodelist)
    {
      int const id = std::get<0>(t);
      assert(nodemap.count(id) == 0); // check for non-repeating IDs
      nodemap[id] = std::make_tuple(std::get<1>(t), std::get<2>(t), std::get<3>(t));
    }

    root = buildTree(nodemap, rootID, nullptr);
  }

  BinaryPTree(BinaryTree<T> const & other)
  {
    root = copyTree(other.root, nullptr);
  }

  BinaryPTree(BinaryTree<T> && other) noexcept
  {
    std::swap(root, other.root);
  }

  ~BinaryPTree()
  {
    tree_ops::erase(root);
  }

  bool operator==(BinaryPTree<T> const & other) const
  {
    return tree_ops::compare(root, other.root, std::equal_to<>{});
  }

  friend std::ostream & operator<<(std::ostream & os, BinaryPTree<T> const & l)
  {
    os << "root" << "\n";
    tree_ops::print(os, l.root, 0);
    os.flush();
    return os;
  }

  [[nodiscard]] size_t depth() const
  {
    return tree_ops::depth(root);
  }

  [[nodiscard]] size_t size() const
  {
    return tree_ops::size(root);
  }

  [[nodiscard]] std::vector<T> values() const
  {
    std::vector<T> vals;
    tree_ops::values(root, vals);
    return vals;
  }

  [[nodiscard]] Node const * find(T const & v) const
  {
    return tree_ops::find(root, v);
  }

  [[nodiscard]] Node const * find_bst(T const & v) const
  {
    return tree_ops::find_bst(root, v);
  }

  ////////////////////////////////////////////////////////////////////////////////

private:

  template<typename ID>
  static Node * buildTree(std::unordered_map<ID, std::tuple<ID,ID,T>> & nodemap, ID const & nodeID, Node * const parent)
  {
    if (nodemap.count(nodeID) == 0) return nullptr;
    std::tuple<ID,ID,T> t = nodemap.at(nodeID);
    nodemap.erase(nodeID);
    Node * const node = new Node;
    node->value = std::get<2>(t);
    node->left  = buildTree(nodemap, std::get<0>(t), node);
    node->right = buildTree(nodemap, std::get<1>(t), node);
    node->parent = parent;
    return node;
  }

  static Node * copyTree(Node const * const node, Node * const parent)
  {
    if (!node) return nullptr;
    Node * copy = new Node;
    copy->value = node->value;
    copy->left = copyTree(node->left, copy);
    copy->right = copyTree(node->right, copy);
    copy->parent = parent;
    return copy;
  }
};

#endif //CTCI_SOLUTIONS_TREE_HPP
