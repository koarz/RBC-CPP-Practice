#pragma once
#include <functional>
#include <ostream>
#include <queue>

namespace rbc {
template <typename T> class BST;
template <typename T> class Node {
public:
  Node(T value, Node *left, Node *right) {
    this->value = value;
    this->left = left;
    this->right = right;
  };
  Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->value = 0;
  }
  Node(const Node &node) {
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
  }
  friend std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << &node << "       => value:" << node.value
       << "        left:" << &node.left << "      right:" << &node.right;
    return os;
  }
  bool operator>(T value) const { return this->value > value; };
  bool operator<(T value) const { return this->value < value; };
  bool operator<=(T value) const { return this->value <= value; };
  bool operator>=(T value) const { return this->value >= value; }
  bool operator==(T value) const { return this->value == value; };
  Node<T> *operator=(Node<T> *other) {
    this->value = other->value;
    this->left = other->left;
    this->right = other->right;
  }
  friend bool operator>(T otherValue, const Node &node) {
    return otherValue > node.value;
  };
  friend bool operator<(T otherValue, const Node &node) {
    return otherValue < node.value;
  };
  friend bool operator>=(T otherValue, const Node &node) {
    return otherValue >= node.value;
  };
  friend bool operator<=(T otherValue, const Node &node) {
    return otherValue <= node.value;
  };
  friend bool operator==(T otherValue, const Node &node) {
    return otherValue == node.value;
  };

  T value{};
  Node *left;
  Node *right;
};

} // namespace rbc

template <typename T> class rbc::BST {
public:
  BST() = default;
  BST(const rbc::BST<T> &other) {
    root = copyTree(other.root);
    node_num_ = other.node_num_;
  }
  rbc::Node<T> *copyTree(rbc::Node<T> *node) {
    if (node == nullptr) {
      return nullptr;
    }
    rbc::Node<T> *newNode = new rbc::Node<T>(*node);
    if (node->left != nullptr) {
      newNode->left = copyTree(node->left);
    }
    if (node->right != nullptr) {
      newNode->right = copyTree(node->right);
    }
    return newNode;
  }
  rbc::BST<T> &operator=(const rbc::BST<T> &other) {
    if (this != &other) {
      deleteTree(root);
      root = copyTree(other.root);
      this->node_num_ = other.node_num_;
    }
    return *this;
  }
  void deleteTree(rbc::Node<T> *node) {
    if (node != nullptr) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }
  // 移动构造函数
  BST(rbc::BST<T> &&other) noexcept { *this = std::move(other); };
  rbc::BST<T> &operator=(rbc::BST<T> &&other) noexcept {
    if (this->root != other.root) {
      this->root = other.root;
      other.root = nullptr;
    }
    return *this;
  };
  // 接受初始化列表
  BST(std::initializer_list<T> initList) {
    for (auto &x : initList) {
      add_node(x);
    }
  }
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
  friend std::ostream &operator<<(std::ostream &os, const BST<T> &bst) {
    std::queue<Node<T> *> q;
    q.push(bst.root);
    while (!q.empty()) {
      auto node = q.front();
      q.pop();
      os << node << std::endl;
      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }
    return os;
  }
  rbc::BST<T> &operator++() {
    std::queue<Node<T> *> q;
    q.push(this->root);
    while (!q.empty()) {
      auto node = q.front();
      q.pop();
      node->value++;
      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }
    return *this;
  }
  rbc::BST<T> operator++(T) {
    auto temp = *this;
    std::queue<Node<T> *> q;
    q.push(this->root);
    while (!q.empty()) {
      auto node = q.front();
      q.pop();
      node->value++;
      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }
    return temp;
  }

private:
  Node<T> *root{nullptr};
  std::size_t node_num_{0};
};

#define RBC_BST_NODE template <typename T> typename rbc::Node<T> *&rbc::BST<T>

#define RBC_BST_NODE_S template <typename T> typename rbc::Node<T> **rbc::BST<T>

#define RBC_BST_VOID template <typename T> void rbc::BST<T>

#define RBC_BST_BOOL template <typename T> bool rbc::BST<T>

#define RBC_BST_SIZE template <typename T> std::size_t rbc::BST<T>

RBC_BST_NODE::get_root() { return this->root; }

RBC_BST_VOID::bfs(std::function<void(rbc::Node<T> *&node)> func) {
  if (this->root == nullptr) {
    return;
  }
  std::queue<Node<T> *> q;
  q.push(this->root);
  while (!q.empty()) {
    auto node = q.front();
    q.pop();
    func(node);
    if (node->left != nullptr) {
      q.push(node->left);
    }
    if (node->right != nullptr) {
      q.push(node->right);
    }
  }
}

RBC_BST_SIZE::length() { return node_num_; }

RBC_BST_BOOL::add_node(T value) {
  rbc::Node<T> *parrent_node = nullptr;
  auto node = root;
  if (node == nullptr) {
    root = new rbc::Node<T>(value, nullptr, nullptr);
    node_num_++;
    return true;
  }

  while (node != nullptr) {
    parrent_node = node;
    if (node->value == value) {
      return false;
    }
    if (value > node->value) {
      node = node->right;
    } else {
      node = node->left;
    }
  }
  if (value < parrent_node->value) {
    parrent_node->left = new rbc::Node<T>(value, nullptr, nullptr);
  } else {
    parrent_node->right = new rbc::Node<T>(value, nullptr, nullptr);
  }
  node_num_++;
  return true;
}

RBC_BST_NODE_S::find_node(T value) {
  auto node = root;
  static rbc::Node<T> *node_ = nullptr;
  while (node->value != value) {
    if (value > node->value) {
      node = node->right;
    } else if (value < node->value) {
      node = node->left;
    } else {
      break;
    }
    if (node == nullptr) {
      return nullptr;
    }
  }
  node_ = node;
  return &node_;
}

RBC_BST_NODE_S::find_parrent(T value) {
  static rbc::Node<T> *parrent_node = nullptr;
  auto node = root;
  if (node->value == value) {
    return nullptr;
  }
  while (node->value != value) {
    if (value > node->value) {
      parrent_node = node;
      node = node->right;
    } else if (value < node->value) {
      parrent_node = node;
      node = node->left;
    }
  }
  return &parrent_node;
}

RBC_BST_NODE_S::find_successor(T value) {
  static rbc::Node<T> *suc;
  auto node = *find_node(value);
  if (node->right != nullptr) {
    node = node->right;
    while (node->left != nullptr) {
      node = node->left;
    }
    suc = node;
  } else {
    auto parrent_node = *find_parrent(value);
    while (parrent_node != nullptr && node != parrent_node->left) {
      node = *find_parrent(node->value);
      parrent_node = node;
      suc = parrent_node;
    }
  }
  return &suc;
}

RBC_BST_BOOL::delete_node(T value) {
  rbc::Node<T> *parrent_node = nullptr;
  auto node = root;
  if (node == nullptr) {
    return false;
  }
  while (node) {
    if (value > node->value) {
      parrent_node = node;
      node = node->right;
    } else if (value < node->value) {
      parrent_node = node;
      node = node->left;
    } else {
      if (node->right == nullptr) {
        if (node == root) {
          root = node->left;
        } else {
          if (node == parrent_node->left) {
            parrent_node->left = node->left;
          } else {
            parrent_node->right = node->left;
          }
        }
        delete node;
      } else if (node->left == nullptr) {
        if (node == root) {
          root = node->right;
        } else {
          if (node == parrent_node->left) {
            parrent_node->left = node->right;
          } else {
            parrent_node->right = node->right;
          }
        }
        delete node;
      } else {
        auto maxleft = node->left;
        auto maxleft_parrent = node;
        while (maxleft->right) {
          maxleft_parrent = maxleft;
          maxleft = maxleft->right;
        }
        node->value = maxleft->value;
        if (maxleft == maxleft_parrent->left) {
          maxleft_parrent->left = maxleft->left;
        } else {
          maxleft_parrent->right = maxleft->left;
        }
        delete maxleft;
      }
      node_num_--;
      return true;
    }
  }
  return false;
}
