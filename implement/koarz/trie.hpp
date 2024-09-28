#pragma once
#include <algorithm>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace rbc {
struct TrieNode {
  // valid为true才代表存在当前字符串
  // 需要注意的是valid仅表示从根节点到当前节点所形成的这个字符串有效
  // 例如插入了字符串: "koarz", "ko" 那么只有 z 和 o 的 valid 为 true
  bool valid{};
  std::vector<std::pair<char, std::shared_ptr<TrieNode>>> next_level_;
};
class Trie;
} // namespace rbc

class rbc::Trie {
  std::shared_ptr<TrieNode> root_;

  void SamePrefixStringHelper(std::shared_ptr<TrieNode>, std::string &,
                              std::vector<std::string> &);

public:
  Trie() : root_(std::make_shared<TrieNode>()) {}

  std::vector<std::string> SamePrefixString(std::string_view);

  void Insert(std::string_view);

  void Remove(std::string_view);

  void RemoveByPrefix(std::string_view);

  bool Exist(std::string_view);
};

// 遍历操作可以封装成函数, 但是我懒, 直接复制用了
inline void rbc::Trie::Insert(std::string_view source) {
  std::shared_ptr<TrieNode> node = root_;
  // 获取根节点为遍历做准备
  for (auto &c : source) {
    // 获取当前节点的 next level数据
    auto &next_level = node->next_level_;
    // 查找下一个字符所在节点, 这里需要用到lambda表达式
    if (auto &&ite = std::find_if(next_level.begin(), next_level.end(),
                                  [&](auto &pair) { return pair.first == c; });

        ite != next_level.end()) {
      // 存在下一个字符的话直接获取对应的节点的sptr更新node
      node = ite->second;
    } else {
      // 不存在的话就需要新建一个节点, 因为数据使用sptr管理, 所以调用make_shared
      // emplace是有返回值的, 这里直接获取对应sptr, 更新node
      auto &[_, ptr] = next_level.emplace_back(c, std::make_shared<TrieNode>());
      node = ptr;
    }
  }
  // 最后node肯定是在最后一个节点, 直接修改valid
  node->valid = true;
}

// remove 函数要做的只是将最后一个节点的 valid 改为 false
inline void rbc::Trie::Remove(std::string_view source) {
  std::shared_ptr<TrieNode> node = root_;
  for (auto &c : source) {
    auto &next_level = node->next_level_;
    if (auto &&ite = std::find_if(next_level.begin(), next_level.end(),
                                  [&](auto &pair) { return pair.first == c; });
        ite != next_level.end()) {
      node = ite->second;
    } else {
      // 前边流程跟Insert一样, 这一步直接return是因为肯定不存在这个字符串
      // 没必要再遍历下去了
      return;
    }
  }
  node->valid = false;
}

inline void rbc::Trie::RemoveByPrefix(std::string_view source) {
  // 这个函数需要移除所有前缀相同的字符串, 一种做法是遍历所有子节点修改valid
  // 但是这种做法太麻烦了, 清空next level就行了, 子节点们会自动析构析构析构...
  // 不过这种做法有一个好处就是减少了资源的析构
  // 创建(以后说不定还会有相同前缀的字符串插入)的开销, 如果子节点数量过于庞大,
  // 那么这个开销也是巨大的
  // 你可以试试另一种做法, 使用dfs算法即可
  std::shared_ptr<TrieNode> node = root_;
  for (auto &c : source) {
    auto &next_level = node->next_level_;
    if (auto &&ite = std::find_if(next_level.begin(), next_level.end(),
                                  [&](auto &pair) { return pair.first == c; });
        ite != next_level.end()) {
      node = ite->second;
    } else {
      return;
    }
  }
  node->valid = false;
  node->next_level_.clear();
}

inline bool rbc::Trie::Exist(std::string_view source) {
  std::shared_ptr<TrieNode> node = root_;
  for (auto &c : source) {
    auto &next_level = node->next_level_;
    if (auto &&ite = std::find_if(next_level.begin(), next_level.end(),
                                  [&](auto &pair) { return pair.first == c; });
        ite != next_level.end()) {
      node = ite->second;
    } else {
      // 一招鲜吃遍天了属于是...
      return false;
    }
  }
  // 最后一个节点可能不存在, 可能被移除, 反正直接返回valid即可
  return node->valid;
}

inline std::vector<std::string>
rbc::Trie::SamePrefixString(std::string_view source) {
  std::shared_ptr<TrieNode> node = root_;
  for (auto &c : source) {
    auto &next_level = node->next_level_;
    if (auto &&ite = std::find_if(next_level.begin(), next_level.end(),
                                  [&](auto &pair) { return pair.first == c; });
        ite != next_level.end()) {
      node = ite->second;
    } else {
      return {};
    }
  }
  std::vector<std::string> res{};
  std::string str{source};
  // 到这里node的所有valid子孙节点都可以加进来了, 使用dfs, bfs都可
  SamePrefixStringHelper(node, str, res);

  return res;
}

inline void rbc::Trie::SamePrefixStringHelper(std::shared_ptr<TrieNode> node,
                                              std::string &str,
                                              std::vector<std::string> &res) {
  if (node->valid) {
    res.push_back(str);
  }
  if (node->next_level_.empty()) {
    return;
  }
  for (auto &[c, ptr] : node->next_level_) {
    str += c;
    SamePrefixStringHelper(ptr, str, res);
    str.pop_back();
  }
}