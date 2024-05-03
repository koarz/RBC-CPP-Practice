#pragma once
namespace rbc {
struct Base {
  int f() { return 0; }
};

struct A : Base {
  int f() { return 1; }
};

struct B : Base {
  int f() { return 2; }
};

struct C : B {
  int f() { return 3; }
};

struct D : A {
  int f() { return 4; }
};
} // namespace rbc