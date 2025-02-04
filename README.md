# 介绍
这是一个用来练习自己实现容器（数据结构）的仓库。
环境：Ubuntu 22.04
`注：强烈建议别用windows，这鬼东西编译时一堆问题，你要是爱折腾那无所谓，如果你爱惜生命，请直接使用虚拟机或者wsl安装ubuntu`
还有一件事，你至少需要的工具有c++各种编译器（clang，g++）、cmake、make。具体安装方法请自己查，这是你必须学习的一部分（如果你以后走计算机这条路的话），查了也不会那就问吧
## 如果你不会Git
首先在控制台输入`git clone https://github.com/koarz/RBC-CPP-Practice.git`这样你就可以获取整个仓库的代码了。
## 如何编译和运行test文件
然后打开项目目录，在`src`文件夹中有你需要实现的容器，你可以自由的实现它们，只要保证能通过所有测试。
在你写完代码之后需要验证的话那就在项目根目录打开控制台（为了保证目录正确），然后输入以下命令：
```
mkdir build
cd build
cmake ..
```
注意，以上命令仅需输入一次，以后就不需要了
最后再输入`make filename_test`，例如想要验证`queue`容器的正确性，那就是`make queue_test`，编译好后执行`./test/queue_test`即可
# 详细教程
详细教程请看[How to start rbc cpp practice](https://a.koarz.top/index.php/archives/34/)，如果还是有不懂的请在评论区留言，或者加群，或者提issue我会尽快解决
