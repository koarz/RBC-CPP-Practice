#include "struct/queue.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
// queue test
namespace rbc {
TEST(QueueTest, BasicTest) {
  queue<int> container;
  container.push(1);
  ASSERT_EQ(container.back(), 1);
  container.push(2);
  ASSERT_EQ(container.back(), 2);
  container.push(3);
  ASSERT_EQ(container.back(), 3);
  container.push(4);
  ASSERT_EQ(container.back(), 4);
  container.push(5);
  ASSERT_EQ(container.back(), 5);
  ASSERT_EQ(container.front(), 1);
  container.pop();
  ASSERT_EQ(container.front(), 2);
  container.pop();
  ASSERT_EQ(container.front(), 3);
  container.pop();
  ASSERT_EQ(container.front(), 4);
  container.pop();
  ASSERT_EQ(container.front(), 5);
  ASSERT_EQ(container.back(), container.front());
  container.pop();
}

TEST(QueueTest, QueueSizeTest) {
  queue<int> container;
  container.push(1);
  ASSERT_EQ(container.size(), 1);
  container.push(2);
  ASSERT_EQ(container.size(), 2);
  container.push(3);
  ASSERT_EQ(container.size(), 3);
  container.push(4);
  ASSERT_EQ(container.size(), 4);
  container.push(5);
  ASSERT_EQ(container.size(), 5);
  container.pop();
  ASSERT_EQ(container.size(), 4);
  container.pop();
  ASSERT_EQ(container.size(), 3);
  container.pop();
  ASSERT_EQ(container.size(), 2);
  container.pop();
  ASSERT_EQ(container.size(), 1);
  container.pop();
  ASSERT_EQ(container.size(), 0);
  ASSERT_TRUE(container.empty());
}

TEST(QueueTest, DifficultTest) {
  queue<int> container;
  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ(container.size(), i);
    container.push(i);
    ASSERT_EQ(container.back(), i);
    ASSERT_EQ(container.front(), 0);
  }
  queue<int> temp;
  temp = container;
  ASSERT_TRUE(container == temp);
  for (int i = 1000; i > 0; i--) {
    ASSERT_EQ(temp.size(), i);
    ASSERT_EQ(temp.front(), 1000 - i);
    temp.pop();
  }
  ASSERT_TRUE(container > temp);
  temp.swap(container);
  ASSERT_TRUE(container < temp);
  ASSERT_TRUE(container != temp);
  for (int i = 1000; i > 0; i--) {
    ASSERT_EQ(temp.size(), i);
    ASSERT_EQ(temp.front(), 1000 - i);
    temp.pop();
  }
  ASSERT_TRUE(container == temp);
}
} // namespace rbc