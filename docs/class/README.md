# class 教程
## 抽象
class 就是cpp中的类，我们都知道cpp是面向对象语言，那么什么是面向对象？这里引用一下百度百科的解释 “面向对象是一种对现实世界理解和抽象的方法”，以我的理解就是将现实世界的事物用基本的数据表示，他们的行为则通过函数实行，举个例子：
```cpp
class Cat {
  double weight;
public:
  Cat(double origin_weight) : weight(origin_weight){}
  void lose_weight(double lose) {
    weight -= lose;
  }
  void add_weight(double add) {
    weight += add;
  }
  double get_weight() {
    return weight;
  }
};
```
比如说我们需要统计小猫的体重变化，这里呢我定义了构造函数需要输入小猫的一开始的体重，然后初始化Cat内部的weight数据，显然weight就是对小猫体重的抽象，我们用数字给他表示了出来。

然后呢小猫的体重有可能增加也有可能减少所以我们提供了两个函数对小猫的体重进行控制，最后因为我们需要统计体重，也就是读取weight的数据内容，所以我们提供了一个`get_weight`函数来访问weight，有人可能有疑问了，我不能直接读取吗？还真不行，这里weight是Cat的`private`成员，我们是无法通过外部进行访问的，又有问题了？这里也没看见private啊，那是因为class默认权限就是private的。而struct默认是public，你可以通过class_access_test来理解。

这是一个很简单的例子，让你理解我们是怎样对现实事物进行抽象的，毕竟万物皆数，理论上来说所有事物都可以抽象成一个类。

这里要注意类和对象要区别开，这里的类只是一些有共同特征的对象的描述（这是我的理解），对象是什么？这里的tom和jerry就是对象，对象是具体的！
```cpp
int main() {
  Cat tom(2.7);
  Cat jerry(1.8);
}
```
## 访问说明符
这部分cppreference介绍的很详细可以直接访问[access](https://zh.cppreference.com/w/cpp/language/access)

在 class/struct 或 union 的 *成员说明* 中定义其后继成员的可访问性。

在派生类声明的 *基类说明符* 中定义它所继承的基类的成员的可访问性。

说明符就三个：public、private、protected。

简单来说private就是除了类本身以及它的友元可以访问，其他的类都不能访问，派生类也不行。

protected则是允许派生类访问，public就是公开，随便访问。

有的人可能通过奇技淫巧访问了private成员，但是这样并没有任何意义，你当然可以尝试，但是别因此而沾沾自喜。
## 构造函数与析构函数
构造函数就是我上边写的`Cat(double origin_weight) : weight(origin_weight){}`这行，我们可以通过构造函数对对象的类成员进行初始化，这里我们就是对weight进行了初始化。

构造函数的形式就是 类名(参数) :后跟着的成员也是会初始化构造的，weight(origin_weight)相当于对weight调用了构造函数，参数是origin_weight。如果你需要进行一些复杂操作那么就可以在 *{}* 里完成。一般情况下我们都会在：后完成对类成员的初始化，在构造函数没有初始化的成员会自动进行默认初始化。

构造函数分为默认构造函数、移动构造函数、拷贝（复制）构造函数，不同的函数有不同的应用场景，部分情况下我们不需要自定义构造函数的，让编译器自己生成就行，有一个需要注意的点是[三五零法则](https://zh.cppreference.com/w/cpp/language/rule_of_three)，一旦我们自定义了构造函数或者复制赋值运算符(operator=)，那么编译器是不会生成其他的函数了，这时候你都需要自己定义一下（有需要的话），不过如果只是进行简单操作那我们只需要在函数后边加上 `=default`即可，例如：
```cpp
class Cat {
  double weight;
public:
  Cat() = default;
  Cat(double origin_weight) : weight(origin_weight){}
  void lose_weight(double lose) {
    weight -= lose;
  }
  void add_weight(double add) {
    weight += add;
  }
  double get_weight() {
    return weight;
  }
};
```
这样我们的Cat就有默认构造函数了，我们写`Cat tom;`就不会再报错了。

拷贝构造函数的一般形式为 `类名(const 类名& other);`我们可以通过拷贝构造函数复制一个对象而不改变原对象数据。继续完善我们的Cat吧：
```cpp
class Cat {
  double weight;
public:
  Cat() = default;
  Cat(double origin_weight) : weight(origin_weight){}
  Cat(const Cat& other) : weight(other.weight){}
  Cat& operator=(const Cat& other) { weight = other.weight; return *this; }
  void lose_weight(double lose) {
    weight -= lose;
  }
  void add_weight(double add) {
    weight += add;
  }
  double get_weight() {
    return weight;
  }
};
```
我们给Cat添加了拷贝构造函数和复制赋值函数，这样我们就可以对Cat对象进行赋值操作了
```cpp
Cat tom(20);
Cat tom_cp1(tom); // 这里调用拷贝构造函数
tom_cp1.add_weight(1.2);
Cat tom_cp2 = tom; // 这里会被优化成调用拷贝构造函数，这时候tom_cp2和tom内部数据一样
tom_cp2 = tom_cp1; // 这里调用复制赋值函数这时候tom_cp2的数据等于tom_cp1的数据，你可以自己试试输出他们的weight验证
```
移动构造函数跟拷贝构造函数不一样 移动构造函数接受的是一个右值，关于CPP值分类可以看这篇文章：[C++的右值引用、移动和值类别系统，你所需要的一切](https://zclll.com/index.php/cpp/value_category.html)，对于右值我们需要将原对象进行移动，移动到新的对象（本质是数据的迁移），移动构造函数的形式是`类名(const 类名&& other);`可以看到只是多了一个&，但是对other进行的操作可不一样，在移动之后other的数据应该是不可用的这是和拷贝构造最大的不同，接下来继续完善Cat！
```cpp
class Cat {
  double weight;
public:
  Cat() = default;
  Cat(double origin_weight) : weight(origin_weight){}
  Cat(const Cat& other) : weight(other.weight){}
  Cat& operator=(const Cat& other) { weight = other.weight; return *this; }
  Cat(const Cat&& other) : weight(std::move(other.weight)){}
  Cat& operator=(const Cat&& other) { weight = std::move(other.weight); return *this; }
  void lose_weight(double lose) {
    weight -= lose;
  }
  void add_weight(double add) {
    weight += add;
  }
  double get_weight() {
    return weight;
  }
};
```
我们这里使用了`std::move`函数，目的就是将原值转换成右值引用然后调用 double 本身的移动复制函数，`std::move`的作用仅仅是转换参数为右值。

如果你看了这些还是很迷糊，那么可以看看这篇文章，有对构造函数区别更详细的解释[换个方式理解移动构造和拷贝构造](https://a.cremache.top/index.php/archives/32/)

讲了这么多构造函数，终于可以开始析构函数的讲解了，析构函数其实也很简单，就是在对象生命周期结束时进行的操作，一般都是对资源进行管理，比如我们在一个类中有一个指针，指向一块new出来的内存，我们在对象生命周期结束时需要释放这块内存不然就会导致内存泄漏，具体长这样：
```cpp
class A{
public:
  A() { data = new int(20); }
  ~A() { delete data; }
  int *data;
};
```
这里我们申请了一个int字节的内存并初始化为20，如果没有在析构时delete这块内存，那么析构函数只会简单的将data也就是这个指针释放，而指针指向的内存不会释放，这样听起来很绕，但还是很好理解的，还不懂就去学C++基础吧，复习一下指针。

tip: 使用类对象对资源进行管理的方法我们成为 ***RAII*** ，具体自行了解，这里就不多说了。
## 继承
我们一般把被继承的类叫基类（父类），继承的类叫子类，继承关系有点像一个网，可以有很多个子类继承一个基类，也可以一个子类继承很多个基类，继承继承的是什么呢？继承的是基类的成员，具体子类能否访问这些成员那么需要看基类的权限怎么设置，以及子类是怎么继承的，我们可以在子类继承基类时添加访问说明符，像这样：
```cpp
class Base{
public:
  int data;
};
class Child : private Base{
  ...
}
```
大部分继承会只继承一个基类，涉及到一些复杂情况的继承我们不做讨论。

继承的作用在我看来就是：提供一个抽象出来有公共特征的基类，子类是有这些特征的一个扩展，这些子类不需要重复定义这些特征，子类有自己的特色，比如人和狗都是哺乳动物，都有四肢，一颗头，两个眼睛，一张嘴，但是人和狗并不是同一物种，各自有独特的特征，这里的基类就是哺乳动物，哺乳动物有头、四肢、眼睛...而派生出的子类也有各自的特色。如果没有继承那么人和狗都得重复定义一些共有特征，两个物种还好，更多的话就太麻烦了。

```cpp
class mammal{
  head;
  extremities;
  ...
};
class human:mammal{
  human have two hands
};
class dog:mammal{
  dog have no hand
};
// 没有继承
class human{
  head;
  extremities;
  ...
  human have two hands
};
class dog{
  head;
  extremities;
  ...
  dog have no hand
};
```
## 多态
**多态**（polymorphism）指为不同 数据类型 的实体提供统一的 接口，或使用一个单一的符号来表示多个不同的类型。

多态的内容很多，深入的学习需要你自己来完成了，这里只简单介绍，帮助你入门，老师领进门，修行在个人嘛。

一般应用多态我们都会用到虚函数(virtual)，在基类中给函数添加`virtual`关键字就声明了一个虚函数，虚函数可以被子类重写，为了可读性一般我们会给重写的虚函数加上override，但是不写其实也不影响。

不同的编译器实现虚函数的方法不同，你自己学习时可能会接触到一个叫虚表的东西，虚表保存虚指针balabala...，好了步入正题。

虚函数像是其他语言的接口，它是一种成员函数，其行为可以在派生类中被覆盖。当使用基类的指针或引用来处理派生类时，对被覆盖的虚函数的调用，将会调用在派生类中定义的行为。这句话怎么理解呢？
```cpp
#include <iostream>
struct A {
  int a = 1;
  virtual void f() { std::cout << "A::f()" << a << std::endl; }
};

struct B : A {
  int b = 2;
  void f() override { std::cout << "B::f()" << a << b << std::endl; }
};

void f(A &a) { a.f(); }

int main() {
  B b = B();
  f(b);
}
```
这段代码创建了一个B类型的对象b，接着调用函数f(A &a)在这个函数中再调用参数a的成员函数f()，如果你运行一下会发现这段代码的输出是`B::f()12`，很简单的例子将上边的两句话都体现了出来，首先是行为被覆盖，我们在B类中重写了f函数，让他的行为变成了`std::cout << "B::f()" << a << b << std::endl;`，所以调用b.f()输出`B::f()12`结果是符合预期的，接着是在`void f(A &a)`中，A &是基类引用，我们传入的参数是派生类B所以`当使用基类的指针或引用来处理派生类时，对被覆盖的虚函数的调用，将会调用在派生类中定义的行为`这句话的作用就体现了出来，这里调用的是派生类B中定义的行为。

虚函数的简单介绍就完了，上边的例子并没有很好的体现出多态，我们只有B继承了A，接下来加上更多的类。
```cpp
#include <iostream>
struct A {
  int a = 1;
  virtual void f() { std::cout << "A::f()" << a << std::endl; }
};

struct B : A {
  int b = 2;
  void f() override { std::cout << "B::f()" << a << b << std::endl; }
};

struct C : A {
  int c = 3;
  void f() override { std::cout << "C::f()" << a << c << std::endl; }
};

struct D : A {
  int d = 4;
  void f() override { std::cout << "D::f()" << a << d << std::endl; }
};

struct E : A {
  int e = 5;
  void f() override { std::cout << "E::f()" << a << e << std::endl; }
};

void f(A &a) { a.f(); }

int main() {
  B b = B();
  f(b);
  C c = C();
  f(c);
  ...
}
```
函数f被我们重写了4次，虽然这些类都继承了A类，但是他们的函数f行为各不相同，这样就简单实现了多态。