#pragma once
#include <functional>
#include <ostream>

namespace rbc {
template <typename T> class BST;
template <typename T> class Node {
public:
  Node(T value, Node *left, Node *right);
  Node();
  Node(const Node &node);
  friend std::ostream &operator<<(std::ostream &os, const Node &node);
  bool operator>(T value) const;
  bool operator<(T value) const;
  bool operator<=(T value) const;
  bool operator>=(T value) const;
  bool operator==(T value) const;
  friend bool operator>(T otherValue, const Node &node);
  friend bool operator<(T otherValue, const Node &node);
  friend bool operator>=(T otherValue, const Node &node);
  friend bool operator<=(T otherValue, const Node &node);
  friend bool operator==(T otherValue, const Node &node);

  T value{};
  Node *left;
  Node *right;
};

} // namespace rbc

template <typename T> class rbc::BST {
public:
  BST() = default;
  // 赋值构造函数
  BST(const rbc::BST<T> &other);
  rbc::BST<T> &operator=(const rbc::BST<T> &other);
  // 移动构造函数
  BST(rbc::BST<T> &&other) noexcept;
  rbc::BST<T> &operator=(rbc::BST<T> &&other) noexcept;
  // 接受初始化列表
  BST(std::initializer_list<T> initList);
  ~BST() {
    std::vector<Node<T> *> nodes;
    bfs([&nodes](rbc::Node<T> *&node) { nodes.push_back(node); });
    for (auto &node : nodes)
      delete node;
  }
  rbc::Node<T> *&get_root();
  void bfs(std::function<void(rbc::Node<T> *&node)> func);
  std::size_t length();
  bool add_node(T value);
  rbc::Node<T> **find_node(T value);
  rbc::Node<T> **find_parrent(T value);
  rbc::Node<T> **find_successor(T value);
  bool delete_node(T value);
  friend std::ostream &operator<<(std::ostream &os, const BST<T> &bst);
  rbc::BST<T> &operator++();
  rbc::BST<T> operator++(T);

private:
  Node<T> *root;
};

#define RBC_BST_NODE template <typename T> typename rbc::Node<T> *&rbc::BST<T>

#define RBC_BST_NODE_S template <typename T> typename rbc::Node<T> **rbc::BST<T>

#define RBC_BST_VOID template <typename T> void rbc::BST<T>

#define RBC_BST_BOOL template <typename T> bool rbc::BST<T>

#define RBC_BST_SIZE template <typename T> std::size_t rbc::BST<T>

RBC_BST_NODE::get_root() {}

RBC_BST_VOID::bfs(std::function<void(rbc::Node<T> *&node)> func) {}

RBC_BST_SIZE::length() {}

RBC_BST_BOOL::add_node(T value) {}

RBC_BST_NODE_S::find_node(T value) {}

RBC_BST_NODE_S::find_parrent(T value) {}

RBC_BST_NODE_S::find_successor(T value) {}

RBC_BST_BOOL::delete_node(T value) {}
