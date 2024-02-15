#include "list.hpp"
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
    c.pop_back();
    EXPECT_EQ(c.back(), i - 1);
  }
  for (int i = 100; i < 200; i++) {
    c.push_front(i);
    EXPECT_EQ(c.front(), i);
  }
  for (int i = 200; i > 100; i--) {
    c.pop_front();
    EXPECT_EQ(c.front(), i - 1);
  }
}

TEST(ListTest, SizeTest) {
  rbc::list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_back(i);
    EXPECT_EQ(c.back(), i);
  }
  EXPECT_EQ(c.size(), 100);
  for (int i = 100; i > 0; i--) {
    c.pop_back();
    EXPECT_EQ(c.back(), i - 1);
  }
  EXPECT_EQ(c.size(), 0);
  EXPECT_TRUE(c.empty());
  for (int i = 100; i < 200; i++) {
    c.push_front(i);
    EXPECT_EQ(c.front(), i);
  }
  EXPECT_EQ(c.size(), 100);
  for (int i = 200; i > 100; i--) {
    c.pop_front();
    EXPECT_EQ(c.front(), i - 1);
  }
  EXPECT_EQ(c.size(), 0);
  EXPECT_TRUE(c.empty());
}

// 最起码应该完成以上测试
TEST(ListTest, OperatorTest) {
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

TEST(ListTest, IteratorTest) {
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
}
} // namespace rbc