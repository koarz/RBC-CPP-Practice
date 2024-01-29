# queue

## 介绍

rbc::queue 类是一种容器适配器，它提供队列的功能——尤其是 FIFO（先进先出）数据结构。

此类模板表现为底层容器的包装器——只提供特定的函数集合。queue 在底层容器尾端推入元素，从首端弹出元素。

## 模板形参

T - 存储的元素类型。

它必须提供下列函数：
- back()
- front()
- push() `该操作会在队尾添加一个元素`
- pop() `该操作弹出队首`

## 成员类型
| **成员类型**        | **定义**       |
|-----------------|--------------|
| value_type      | T            |
| size_type       | unsigned int |
| reference       | T&           |
| const_reference | const T&     |

## 成员函数
1. **成员函数**
   - `(构造函数)` | `构造queue`
   - `(析构函数)` | `析构queue`
   - `operator=` | `赋值给容器`
2. **元素访问**
   - `front` | `访问第一个元素`
   - `back` | `访问最后一个元素`
3. **容量**
   - `empty` | `检查容器是否为空`
   - `size` | `返回元素数`
4. **修改器**
   - `push` | `向队列尾部插入元素`
   - `pop` | `移除首个元素`
   - `emplace` | `在尾部原位构造元素`
   - `swap` | `交换内容`
## 非成员函数
   - `operator== | operator< | operator> | operator>= | operator<= | operator !=` | `按字典序比较两个queue的值`