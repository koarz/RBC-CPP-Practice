cmake_minimum_required(VERSION 3.14)

# 在这里添加你添加的头文件路径
set(LIBRARY_LIBS
    include/queue.h
    queue.cpp
)

add_library(library ${LIBRARY_LIBS})
set_target_properties(library PROPERTIES LINKER_LANGUAGE CXX)