#include "stack.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>

namespace rbc {
TEST(StackTest, BasicTest) {
  stack<int> st;
  st.push(50);
  EXPECT_EQ(st.top(), 50);
  st.push(20);
  EXPECT_EQ(st.top(), 20);
  st.pop();
  EXPECT_EQ(st.top(), 50);
  st.pop();
  st.pop();
}

TEST(StackTest, SizeTest) {
  stack<int> st;
  for (int i = 0; i < 100; i++) {
    st.push(i * 2);
    EXPECT_EQ(st.top(), i * 2);
  }
  EXPECT_EQ(st.size(), 100);
  EXPECT_FALSE(st.empty());
  for (int i = 99; i >= 0; i--) {
    EXPECT_EQ(st.top(), i * 2);
    st.pop();
  }
  EXPECT_EQ(st.size(), 0);
  EXPECT_TRUE(st.empty());
}

TEST(StackTest, SwapTest) {
  stack<int> st, su;
  for (int i = 0; i < 100; i++) {
    st.push(i * 2);
  }
  su.swap(st);
  EXPECT_EQ(su.size(), 100);
  EXPECT_FALSE(su.empty());
  EXPECT_EQ(st.size(), 0);
  EXPECT_TRUE(st.empty());
  for (int i = 99; i >= 0; i--) {
    EXPECT_EQ(su.top(), i * 2);
    su.pop();
  }
}

TEST(StackTest, OperatorTest) {
  stack<int> st, su;
  for (int i = 0; i < 100; i++) {
    st.push(i * 2);
    su.push(i);
  }
  EXPECT_TRUE(st > su);
  EXPECT_TRUE(st >= su);
  st.swap(su);
  EXPECT_TRUE(st < su);
  EXPECT_TRUE(st <= su);
  EXPECT_TRUE(st != su);
  su = st;
  EXPECT_TRUE(st == su);
}
} // namespace rbc