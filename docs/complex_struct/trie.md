# Trie(字典树)
字典树，英文名 trie。顾名思义，就是一个像字典一样的树。

关于字典树的介绍可以看:[Trie](https://oi-wiki.org/string/trie/)

## 任务
### Insert
函数声明为`void Insert(std::string_view);`，这里参数是 `std::string_view` 类型的变量，该类型变量可减少string的拷贝开销，它内部保存了一个CharType类型的指针（char w_char...），需要由程序员保证string_view的生命周期不会超过指向数组的生命周期

你需要实现插入字符串的操作, 给你一些字符串你应该怎么将这些字符串结合变成一棵树?

举个例子, 插入 `"RedA" "RedB" "RedC"` 最后的树应该长这样
```txt
              root
             / 
           R
          /  
         e
       /
      d
  /   |  \
  A   B   C
```
如果又插入了`"Koarz"`那么整棵树应该是这样
```txt
              root
             /   \
           R       K
          /         \
         e           o
       /              \
      d                a
  /   |  \              \
  A   B   C              r
                          \
                           z 
```
### Exist
Exist需要判断是否存在给定的字符串

如果插入了 `"Koarz"` 那么整棵树只有 `"Koarz"` 求exist是true, 其他的任何值 包括他的子串都应该是false

### Remove
在Trie中移除给定字符串, 你需要注意的是 如果树中存在字符串 "Ko" "Koarz" 时, 如果你移除了 "Ko" 那么是不能对 "Koarz" 有影响的

你不需要考虑Trie中是否存在所给的字符串, 也就是说不需要在Remove "Koa" 时因为它不存在而抛出异常或者做其他动作

### RemoveByPrefix
给你一个字符前缀, 移除拥有该前缀的所有字符串 比如Trie中存在 "Ko" "Koarz" "Red", 当调用`RemoveByPrefix("Ko")`后整棵树只应该存在 "Red"

### SamePrefixString
你需要返回所有含有给定前缀的字符串 也就是说Trie中存在 "Ko" "Koarz" "Red", 当调用`SamePrefixString("Ko")`后你需要返回 "Ko" 和 "Koarz"

返回的顺序不做要求也就是说返回顺序为 "Ko", "Koarz" 或者 "Koarz", "Ko" 都行