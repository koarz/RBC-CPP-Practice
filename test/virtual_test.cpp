#include "class/virtual.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
namespace rbc {
TEST(VirtualTest, EasyTest) {
  A a;
  B b;
  C c;
  D d;
  ASSERT_EQ(a.f(), 1);
  ASSERT_EQ(b.f(), 2);
  ASSERT_EQ(c.f(), 3);
  ASSERT_EQ(d.f(), 4);
}

} // namespace rbc