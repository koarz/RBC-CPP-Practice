#include "complex_struct/skip_list.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <climits>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

namespace rbc {
TEST(SkipListTest, SequenceInsertTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
}

TEST(SkipListTest, GetTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(skip_list.Get(i), i + 100);
  }
}

TEST(SkipListTest, InsertUpdateTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(skip_list.Get(i), i + 100);
  }
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 200);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(skip_list.Get(i), i + 200);
  }
}

TEST(SkipListTest, GetThrowTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
  for (int i = 100; i < 200; i++) {
    EXPECT_THROW(skip_list.Get(i), std::runtime_error);
  }
}

TEST(SkipListTest, DisorderInsertTest) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, INT_MAX);
  SkipList<int, int> skip_list(5);
  std::map<int, int> data;
  for (int i = 0; i < 1000; i++) {
    int k = distrib(gen), v = distrib(gen);
    data[k] = v;
    skip_list.Insert(std::make_pair(k, v));
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    EXPECT_EQ(skip_list.Get(it->first), it->second);
  }
}

TEST(SkipListTest, RemoveTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
  for (int i = 50; i < 100; i++) {
    skip_list.Remove(i);
  }
  for (int i = 0; i < 50; i++) {
    EXPECT_EQ(skip_list.Get(i), i + 100);
  }
  for (int i = 50; i < 100; i++) {
    EXPECT_THROW(skip_list.Get(i), std::runtime_error);
  }
}

TEST(SkipListTest, DISABLED_IteratorTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
  int i = 0;
  for (auto it = skip_list.Begin(); it != skip_list.End(); ++it, i++) {
    EXPECT_EQ(skip_list.Get(i), i + 100);
  }
}

TEST(SkipListTest, DISABLED_FindTest) {
  SkipList<int, int> skip_list(5);
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i + 100);
  }
  for (int i = 1; i < 100; i += 2) {
    skip_list.Remove(skip_list.Find(i));
  }
  for (int i = 0; i < 100; i += 2) {
    EXPECT_EQ(skip_list.Get(i), i + 100);
  }
  for (int i = 1; i < 100; i += 2) {
    EXPECT_THROW(skip_list.Get(i), std::runtime_error);
  }
}
} // namespace rbc