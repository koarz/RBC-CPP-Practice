# BST

## 介绍
本项目基于AP1400-2-HW3(经过了模板编程的升级，还给出了基本框架。)。在这个项目中，我们将实现一个二叉搜索树（BST）。二叉树是一种树形图，其中节点最多只能有 2 个子节点。二叉搜索树是一种二叉树，其中每个节点的右子节点的值大于左节点的值。我们将实现 2 个类，分别为Node和BST，基本的框架已经给出。

**请注意，本项目的难度较大，建议做完前面四个在来做这个。**


## 函数

### Node类

## 要求

### 1.
每个节点都有一个值，可以使用左右指针指向其子节点。如果一个或多个子项不存在，则 nullptr 分配给它们。

### 2.
重载 << 算符，以便能够以 std::cout 的方式在一行中打印节点，输出应包含节点的地址、节点的值、节点的左子地址和节点的右子地址。

### 3.

实现与T的比较，要求支持以下形式的比较：

    node > 4     node >= 5	node < 6	node <= 5
    node == 3    5 < node	6 <= node
 	2 > node	 2 >= node	3 == node

## BST类

### 1.get_root

get_root返回私有成员变量 root。

### 2. bfs

bfs 广度优先搜索 （BFS） 是一种通过遍历每个节点来搜索树的算法;实现这个算法！

此函数的输入为 **std::function** ，此类型的行为类似于指向函数的指针，并且可以像普通函数或 lambda 函数一样包装 c++ 中的任何可调用对象。您将在本项目中使用 **Lambda** 函数，因此请随时搜索和了解它们。

### 3. length

length 返回 BST 中存在的节点数。

### 4. add_node

add_node 在适当的位置向 BST 添加一个新节点。注意：你不应能够添加树中已存在的值。

### 5. find_node

find_node在树中查找具有指定值的节点，并返回指向该节点指针的指针。

注意：不要使用 BFS 算法来查找结点，而是使用二叉搜索树的属性。

### 6. find_parrent

find_parrent查找具有指定值的节点的 parrent 节点，并返回指向该 parrent 指针的指针。
注意：不要使用 BFS 算法来查找父结点。

### 7. find_successor 

find_successor查找具有指定值的节点的后继节点。

### 8. delete_node

delete_node删除具有指定值的节点。如果没有具有该值的此类节点，则返回 false。

### 9. std::cout

std：：cout 实现运 << 算符，以便能够以 std::cout 美观的方式打印 BST。为此，请打印 BST 的每个节点。如果您设法生成与以下完全相同的输出，您将获得额外的分数（星星是输出的一部分）。

	```cpp
	********************************************************************************
	0x188dee70       => value:25        left:0x188dedd0      right:0x188dedf0      
	0x188dedd0       => value:10        left:0x188dee30      right:0x188ded90      
	0x188dedf0       => value:50        left:0               right:0x188dee50      
	0x188dee30       => value:7         left:0               right:0               
	0x188ded90       => value:15        left:0               right:0               
	0x188dee50       => value:53        left:0               right:0               
	binary search tree size: 6
	******************************************************************************** 
	```

### 10. operator++

operator++ 实现这两个 ++ 运算符，以便使每个结点自增1。


注意：不要忘记 和 ++bst 之间的区别 bst++ 。

### 11. 析构函数

构造函数 为类实现 3 个构造函数：I） defualt 构造函数。II） 复制构造函数。III） 移动构造函数。

### 12. operator=
 实现 operator= （拷贝构造和移动构造） 的两个版本。

## debug
如果你想要debug，使用以下代码：
```cpp
if (true) // make false to run unit tests  
{ 
	// debug section 
}  
else  
{  
	::testing::InitGoogleTest(&argc, argv);  
	std::cout << "RUNNING TESTS ..." << std::endl;  
	int ret{RUN_ALL_TESTS()};  
	if (!ret)  
		std::cout << "<<<SUCCESS>>>" << std::endl;  
	else  
	  std::cout << "FAILED" << std::endl;  
}  
return 0;
```
