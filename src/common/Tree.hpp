#ifndef CTCI_SOLUTIONS_TREE_HPP
#define CTCI_SOLUTIONS_TREE_HPP

#include <initializer_list>
#include <ostream>
#include <unordered_map>
#include <vector>
#include <cassert>

/**
 * @brief Simple wrapper struct for a binary tree
 *
 * Main goal is to automate copying/printing/destruction of the tree.
 * Constructor from a node-tuple-list is provided to facilitate testing.
 * Normally tree construction would be performed manually in problems.
 */
template <typename T>
struct BinaryTree
{
  struct Node
  {
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
    deleteTree(root);
  }

  bool operator==(BinaryTree<T> const & other)
  {
    return compareTree(root, other.root, std::equal_to<>{});
  }

  friend std::ostream & operator<<(std::ostream & os, BinaryTree<T> const & l)
  {
    os << "root" << "\n";
    l.printTree(os, l.root, 0);
    os.flush();
    return os;
  }

  [[nodiscard]] size_t depth() const
  {
    return depthTree(root);
  }

  [[nodiscard]] size_t size() const
  {
    return sizeTree(root);
  }

  [[nodiscard]] std::vector<T> values() const
  {
    std::vector<T> res;
    dfsTree(root, res);
    return res;
  }

  ////////////////////////////////////////////////////////////////////////////////

  template <typename ID>
  static Node * buildTree(std::unordered_map<ID, std::tuple<ID,ID,T>> & nodemap, ID const & nodeID)
  {
    if (nodemap.count(nodeID) == 0) return nullptr;
    std::tuple<ID,ID,T> t = nodemap.at(nodeID);
    nodemap.erase(nodeID);
    Node * node = new Node;
    node->value = std::get<2>(t);
    node->left  = buildTree(nodemap, std::get<0>(t));
    node->right = buildTree(nodemap, std::get<1>(t));
    return node;
  }

  static Node * copyTree(Node const * const node)
  {
    if (!node) return nullptr;
    Node * copy = new Node;
    copy->value = node->value;
    copy->left = copyTree(node->left);
    copy->right = copyTree(node->right);
    return copy;
  }

  template<typename Comp>
  static bool compareTree(Node const * a, Node const * const b, Comp comp)
  {
    if (a == b) return true;    // same node trivial case
    if (!a != !b) return false; // both null or non-null
    return comp(a->value, b->value)
        && compareTree(a->left, b->left, comp)
        && compareTree(a->right, b->right, comp);
  }

  static void printTree(std::ostream & os, Node const * const node, int level)
  {
    os << std::string(level * 2, ' ') << "-> ";
    if (!node)
    {
      os << "null\n";
    }
    else
    {
      os << node->value << "\n";
      printTree(os, node->left, level + 1);
      printTree(os, node->right, level + 1);
    }
  }

  static void deleteTree(Node * const node)
  {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  static size_t depthTree(Node const * const node)
  {
    if (!node) return 0;
    return 1 + std::max(depthTree(node->left), depthTree(node->right));
  }

  static size_t sizeTree(Node const * const node)
  {
    if (!node) return 0;
    return 1 + sizeTree(node->left) + sizeTree(node->right);
  }

  static void dfsTree(Node const * const node, std::vector<T> & values)
  {
    if (!node) return;
    dfsTree(node->left, values);
    values.push_back(node->value);
    dfsTree(node->right, values);
  }
};

#endif //CTCI_SOLUTIONS_TREE_HPP
