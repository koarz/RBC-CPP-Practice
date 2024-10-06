# SkipList
SkipList也就是跳表具体是个怎样的数据结构你应该自己查(我懒得写), 毕竟能来尝试这个那么你应该有不错的自学能力了

那么接下来就是简单介绍任务
## Insert
Insert的参数是一个 Key 和一个 Value , 很显然你需要将他们插入这条跳表中, 如果表中已经存在相同的 Key 那么你应该更新 Value
另一个版本是传入KV对, 你也需要对这种情况做处理

## Remove
Remove函数有两个版本, 一个是输入Key的版本 另一个是使用迭代器删除的版本如果你不实现迭代器的话忽略这部分

## Get
根据Key返回对应的Value如果不存在对应key直接抛出`std::runtime_error("The Key Have Not Mapping Any Value.\n")`异常

## Find
通过Key查找, 返回对应迭代器, 如果不存在对应值则返回 `End()`