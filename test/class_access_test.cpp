#include "class/class_access.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace rbc {
TEST(ClassAccessTest, AccessCat) {
  Cat tom(10.3);
  tom.add_weight(10.2);
  EXPECT_EQ(tom.get_weight(), 10.3 + 10.2);
  tom.lose_weight(3.4);
  EXPECT_EQ(tom.get_weight(), 10.3 + 10.2 - 3.4);
}
TEST(ClassAccessTest, AccessDog) {
  Dog spike(1);
  spike.update_community_num(20);
  EXPECT_EQ(spike.get_community_num(), 20);
}
} // namespace rbc
