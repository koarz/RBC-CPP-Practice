#include "struct/list.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
namespace rbc {
TEST(ListTest, BasicTest) {
  rbc::list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_back(i);
    EXPECT_EQ(c.back(), i);
  }
  for (int i = 100; i > 0; i--) {
    EXPECT_EQ(c.back(), i - 1);
    c.pop_back();
  }
  for (int i = 100; i < 200; i++) {
    c.push_front(i);
    EXPECT_EQ(c.front(), i);
  }
  for (int i = 200; i > 100; i--) {
    EXPECT_EQ(c.front(), i - 1);
    c.pop_front();
  }
  c.pop_front();
  c.pop_back();
}

TEST(ListTest, SizeTest) {
  rbc::list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_back(i);
    EXPECT_EQ(c.back(), i);
  }
  EXPECT_EQ(c.size(), 100);
  for (int i = 100; i > 0; i--) {
    EXPECT_EQ(c.back(), i - 1);
    c.pop_back();
  }
  EXPECT_EQ(c.size(), 0);
  EXPECT_TRUE(c.empty());
  for (int i = 100; i < 200; i++) {
    c.push_front(i);
    EXPECT_EQ(c.front(), i);
  }
  EXPECT_EQ(c.size(), 100);
  for (int i = 200; i > 100; i--) {
    EXPECT_EQ(c.front(), i - 1);
    c.pop_front();
  }
  EXPECT_EQ(c.size(), 0);
  EXPECT_TRUE(c.empty());
  c.resize(100, 100);
  EXPECT_EQ(c.size(), 100);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(c.back(), 100);
    c.pop_back();
  }
  c.resize(100, 100);
  c.resize(120, 200);
  for (int i = 100; i < 120; i++) {
    EXPECT_EQ(c.back(), 200);
    c.pop_back();
  }
  c.resize(0, 0);
  EXPECT_EQ(c.size(), 0);
  EXPECT_TRUE(c.empty());
}

TEST(ListTest, SwapTest) {
  rbc::list<int> a, c;
  for (int i = 0; i < 100; i++) {
    c.push_back(i);
    a.push_back(100 + i);
  }
  a.swap(c);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(c.front(), a.front() + 100);
    c.pop_front();
    a.pop_front();
  }
  for (int i = 100; i < 200; i++) {
    c.push_back(i);
  }
  for (int i = 200; i < 250; i++) {
    a.push_back(i);
  }
  a.swap(c);
  EXPECT_EQ(c.size(), 50);
  EXPECT_EQ(a.size(), 100);
  for (int i = 0; i < 100; i++) {
    if (i < 50)
      EXPECT_EQ(c.front(), a.front() + 100);
    else
      EXPECT_EQ(a.front(), i + 100);
    c.pop_front();
    a.pop_front();
  }
}

// 最起码应该完成以上测试，如果你想进行以下测试，删掉DISABLED_即可
TEST(ListTest, DISABLED_OperatorTest) {
  // 减了好多函数，也就只能测个赋值了
  rbc::list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_back(i);
  }
  rbc::list<int> a;
  a = c;
  EXPECT_EQ(c.size(), 100);
  EXPECT_EQ(a.size(), 100);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(c.back(), a.back());
    a.pop_back();
    c.pop_back();
  }
}

TEST(ListTest, DISABLED_IteratorTest) {
  rbc::list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_back(i);
  }
  int j = 0;
  for (auto i = c.begin(); i != c.end(); ++i, ++j) {
    EXPECT_EQ(*i, j);
    *i = 1000;
  }
  for (auto i = c.begin(); i != c.end(); ++i) {
    EXPECT_EQ(*i, 1000);
  }
  auto it = c.begin();
  c.insert(it, 10);
  EXPECT_EQ(c.front(), 10);
  EXPECT_EQ(c.size(), 101);
  c.erase(it);
  EXPECT_EQ(c.size(), 100);
  c.erase(c.begin());
  EXPECT_EQ(c.front(), 1000);
  EXPECT_EQ(c.size(), 99);
}
} // namespace rbc