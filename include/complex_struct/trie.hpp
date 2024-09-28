#pragma once
#include <string>
#include <vector>

namespace rbc {
class Trie;
} // namespace rbc

class rbc::Trie {
public:
  std::vector<std::string> SamePrefixString(std::string_view);

  void Insert(std::string_view);

  void Remove(std::string_view);

  void RemoveByPrefix(std::string_view);

  bool Exist(std::string_view);
};

inline void rbc::Trie::Insert(std::string_view source) {}

inline void rbc::Trie::Remove(std::string_view source) {}

inline void rbc::Trie::RemoveByPrefix(std::string_view source) {}

inline bool rbc::Trie::Exist(std::string_view source) { return false; }

inline std::vector<std::string>
rbc::Trie::SamePrefixString(std::string_view source) {
  return {};
}
