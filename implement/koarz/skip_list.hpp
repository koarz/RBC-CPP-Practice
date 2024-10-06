#pragma once

#include <memory>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

namespace rbc {
template <typename _K, typename _V> struct SkipListNode {
  // next 指针指向下个节点 next为 0 代表在当前节点最高
  std::vector<std::shared_ptr<SkipListNode>> next_;
  // 数据直接保存在这里
  std::pair<_K, _V> kv_;
  SkipListNode(unsigned int level) : next_(level, nullptr) {}
};
template <typename _K, typename _V> class SkipList;
} // namespace rbc

template <typename _K, typename _V> class rbc::SkipList {
  const unsigned int max_level_;
  std::shared_ptr<SkipListNode<_K, _V>> root_;

  unsigned int GetRandomLevel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, max_level_);
    return distrib(gen);
  }

  void FindLess(std::shared_ptr<SkipListNode<_K, _V>> node, _K &key,
                std::vector<std::shared_ptr<SkipListNode<_K, _V>>> &lord) {
    for (auto &p : node->next_) {
      if (p == nullptr) {
        lord.push_back(node);
        continue;
      }
      if (p->kv_.first < key) {
        FindLess(p, key, lord);
        return;
      }
      lord.push_back(node);
    }
  }

  void FindLessEqual(std::shared_ptr<SkipListNode<_K, _V>> node, const _K &key,
                     std::vector<std::shared_ptr<SkipListNode<_K, _V>>> &lord) {
    for (auto &p : node->next_) {
      if (p == nullptr) {
        lord.push_back(node);
        continue;
      }
      if (p->kv_.first < key) {
        FindLessEqual(p, key, lord);
        return;
      }
      if (p->kv_.first == key) {
        lord.push_back(p);
      } else {
        lord.push_back(node);
      }
    }
  }

public:
  explicit SkipList(unsigned int max_level)
      : max_level_(max_level),
        root_(std::make_shared<SkipListNode<_K, _V>>(max_level_)){};
  ~SkipList() = default;

  class Iterator {
    std::shared_ptr<SkipListNode<_K, _V>> node_;

  public:
    Iterator(std::shared_ptr<SkipListNode<_K, _V>> node) : node_(node) {}
    Iterator &operator++() {
      node_ = *node_->next_.rbegin();
      return *this;
    }
    bool operator!=(Iterator other) { return node_ != other.node_; }
    bool operator==(Iterator other) { return node_ == other.node_; }
    std::pair<_K, _V> &operator*() { return node_->kv_; }
    std::pair<_K, _V> &operator->() { return node_->kv_; }
  };

  template <typename PAIR>
    requires requires(PAIR x) {
      x.first;
      x.second;
    }
  void Insert(PAIR &&kv) {
    Insert(kv.first, kv.second);
  }

  template <typename KTp, typename VTp> void Insert(KTp &&key, VTp &&value) {
    std::vector<std::shared_ptr<SkipListNode<_K, _V>>> lord;
    auto level = GetRandomLevel();
    FindLessEqual(root_, key, lord);
    // 更新值
    if (*lord.rbegin() != root_ && (*lord.rbegin())->kv_.first == key) {
      (*lord.rbegin())->kv_.second = value;
      return;
    }
    std::shared_ptr<SkipListNode<_K, _V>> node =
        std::make_shared<SkipListNode<_K, _V>>(level);
    auto ite = node->next_.begin();
    for (int i = max_level_ - level; i < max_level_; i++) {
      int lord_level = i - max_level_ + lord[i]->next_.size();
      *ite = lord[i]->next_[lord_level];
      lord[i]->next_[lord_level] = node;
      ite++;
    }
    node->kv_ = std::make_pair(key, value);
  }

  template <typename KTp>
  //  requires std::is_same_v<std::remove_reference_t<KTp>, _K>
  void Remove(KTp &&key) {
    std::vector<std::shared_ptr<SkipListNode<_K, _V>>> lord;
    FindLess(root_, key, lord);
    if (*lord.rbegin() != root_ &&
        (*(*lord.rbegin())->next_.rbegin())->kv_.first == key) {
      auto node = (*(*lord.rbegin())->next_.rbegin());
      auto ite = node->next_.begin();
      auto level = node->next_.size();
      for (int i = max_level_ - level; i < max_level_; i++) {
        int lord_level = i - max_level_ + lord[i]->next_.size();
        lord[i]->next_[lord_level] = *ite;
        ite++;
      }
      return;
    }
  }

  void Remove(SkipList<_K, _V>::Iterator ite) { Remove((*ite).first); }

  template <typename KTp> _V &Get(KTp &&key) {
    std::vector<std::shared_ptr<SkipListNode<_K, _V>>> lord;
    FindLessEqual(root_, key, lord);
    if ((*lord.rbegin())->kv_.first == key) {
      return (*lord.rbegin())->kv_.second;
    }
    throw std::runtime_error("The Key Have Not Mapping Any Value.\n");
  }

  template <typename KTp> Iterator Find(KTp &&key) {
    std::vector<std::shared_ptr<SkipListNode<_K, _V>>> lord;
    FindLessEqual(root_, key, lord);
    if ((*lord.rbegin())->kv_.first == key) {
      return Iterator(*lord.rbegin());
    }
    return End();
  }

  Iterator Begin() { return Iterator(*root_->next_.rbegin()); }

  Iterator End() { return Iterator(nullptr); }
};