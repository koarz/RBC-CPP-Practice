#include "complex_struct/trie.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace rbc {
TEST(TrieTest, InsertTest) {
  Trie trie;
  trie.Insert("Hello World");
  trie.Insert("I Love RBC");
}

TEST(TrieTest, ExistTest) {
  Trie trie;
  trie.Insert("Koarz");
  trie.Insert("KoKo");
  trie.Insert("Koooooarz");
  EXPECT_TRUE(trie.Exist("Koarz"));
  EXPECT_TRUE(trie.Exist("KoKo"));
  EXPECT_TRUE(trie.Exist("Koooooarz"));

  EXPECT_FALSE(trie.Exist("K"));
  EXPECT_FALSE(trie.Exist("Ko"));
  EXPECT_FALSE(trie.Exist("Koa"));
  EXPECT_FALSE(trie.Exist("Koar"));
  EXPECT_FALSE(trie.Exist("KoK"));
  EXPECT_FALSE(trie.Exist("Koo"));
  EXPECT_FALSE(trie.Exist("Kooo"));
  EXPECT_FALSE(trie.Exist("Koooo"));
  EXPECT_FALSE(trie.Exist("Kooooo"));
  EXPECT_FALSE(trie.Exist("Koooooa"));
  EXPECT_FALSE(trie.Exist("Koooooar"));
}

TEST(TrieTest, RemoveTest) {
  Trie trie;
  trie.Insert("Koarz");
  trie.Insert("KoKo");
  trie.Insert("Koooooarz");

  trie.Remove("Koarz");
  EXPECT_FALSE(trie.Exist("Koarz"));
  trie.Remove("KoKo");
  EXPECT_FALSE(trie.Exist("KoKo"));
  trie.Remove("Koooooarz");
  EXPECT_FALSE(trie.Exist("Koooooarz"));
}

TEST(TrieTest, RemoveByPrefixTest) {
  Trie trie;
  trie.Insert("Koarz");
  trie.Insert("KoKo");
  trie.Insert("Koooooarz");

  trie.RemoveByPrefix("Ko");

  EXPECT_FALSE(trie.Exist("Koarz"));
  EXPECT_FALSE(trie.Exist("KoKo"));
  EXPECT_FALSE(trie.Exist("Koooooarz"));
}

TEST(TrieTest, SamePrefixStringTest) {
  Trie trie;

  std::vector<std::string> container{"Koarz", "KoKo", "Koooooarz"};

  for (auto &s : container) {
    trie.Insert(s);
  }

  auto res = trie.SamePrefixString("Ko");

  EXPECT_EQ(res.size(), container.size());

  for (auto &s : container) {
    EXPECT_TRUE(std::find(res.begin(), res.end(), s) != res.end());
  }
}

} // namespace rbc
