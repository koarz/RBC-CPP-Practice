#pragma once
namespace rbc {
// 该练习所有的数据都应该是无法通过对象访问的，不要全部设为public，这样没有任何意义！
class Cat {
  Cat(double origin_weight) : weight(origin_weight) {}
  double get_weight() { return weight; }
  void lose_weight(double lose) { weight -= lose; }
  void add_weight(double add) { weight += add; }
  double weight;
};

class Animal {
  unsigned community_num{0};
  Animal(unsigned num) : community_num(num) {}
};
class Dog : Animal {
  Dog(unsigned num) : Animal(num) {}
  unsigned get_community_num() { return community_num; }
  void update_community_num(unsigned new_num) { community_num = new_num; }
};
} // namespace rbc