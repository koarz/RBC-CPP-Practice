# 介绍
你需要在这个文件夹中实现对应的容器也就是`*.hpp`文件。

你可以先看看`*.hpp`文件中有哪些数据成员或者函数，看一看`*.md`文档中的描述，这或许对你实现容器有所帮助。

实现之后你可以运行对应的`*_test.cpp`文件来验证你的实现是否正确。

你可以在不改变原有类函数以及成员的情况下随意添加一些新的函数或者成员甚至新的类来帮助你实现这个容器。

如果你会写test的话，可以提交pr，添加新的容器模板

## 如何添加新的模板
在当前目录下的include目录中添加你需要的头文件，并给你的class添加合适的成员函数，之后在当前目录的CMakeLists.txt文件中的set(LIBRARY_HEAD) 中写入头文件的名字，再到test文件夹里写好对应的test文件就可以提交了。