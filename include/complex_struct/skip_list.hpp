#pragma once

#include <utility>

namespace rbc {
template <typename _K, typename _V> class SkipList;
} // namespace rbc

template <typename _K, typename _V> class rbc::SkipList {
  const unsigned int max_level_;

public:
  explicit SkipList(unsigned int max_level) : max_level_(max_level){};
  ~SkipList() = default;

  class Iterator {

  public:
    Iterator &operator++() { return *this; }
    bool operator!=(Iterator other) { return true; }
    bool operator==(Iterator other) { return true; }
    std::pair<_K, _V> &operator*() { return std::pair<_K, _V>(); }
    std::pair<_K, _V> &operator->() { return std::pair<_K, _V>(); }
  };

  template <typename PAIR>
    requires requires(PAIR x) {
      x.first;
      x.second;
    }
  void Insert(PAIR &&kv) {}

  template <typename KTp, typename VTp> void Insert(KTp &&key, VTp &&value) {}

  template <typename KTp> void Remove(KTp &&key) {}

  void Remove(SkipList<_K, _V>::Iterator ite) {}

  template <typename KTp> _V &Get(KTp &&key) {}

  template <typename KTp> Iterator Find(KTp &&key) { return End(); }

  Iterator Begin() { return Iterator(); }

  Iterator End() { return Iterator(); }
};
