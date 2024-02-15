#include "forward_list.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace rbc {
TEST(ForwardListTest, BasicTest) {
  rbc::forward_list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_front(i);
    EXPECT_EQ(c.front(), i);
  }
  for (int i = 100; i > 0; i--) {
    c.pop_front();
    EXPECT_EQ(c.front(), i - 1);
  }
}
TEST(ForwardListTest, SizeTest) {
  rbc::forward_list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_front(i);
    EXPECT_EQ(c.front(), i);
  }
  c.resize(50, 6);
  EXPECT_EQ(c.max_size(), 50);
  c.clear();
  c.resize(100, 6);
  EXPECT_EQ(c.max_size(), 100);
  EXPECT_EQ(c.front(), 6);
}

TEST(ForwardListTest, OperatorTest) {
  rbc::forward_list<int> c;
  for (int i = 0; i < 100; i++) {
    c.push_front(i);
  }
  rbc::forward_list<int> a;
  a = c;
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(c.front(), a.front());
    a.pop_front();
    c.pop_front();
  }
}

TEST(ForwardListTest, IteratorTest) {
  rbc::forward_list<int> c;
  rbc::forward_list<int> a;
  for (int i = 0; i < 100; i++) {
    c.push_front(i);
    a.push_front(100 - i);
  }
  EXPECT_EQ(&a == &c, false);
  int j = 0;
  for (auto i = c.begin(), k = a.begin(); i != c.end() && k != a.end();
       ++i, ++j, ++k) {
    EXPECT_EQ(*i, j);
    *i = 1000;
    *k = 1000;
  }
  for (auto i = c.begin(); i != c.end(); ++i) {
    EXPECT_EQ(*i, 1000);
  }
  EXPECT_EQ(&a == &c, true);
}
} // namespace rbc
