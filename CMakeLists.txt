cmake_minimum_required(VERSION 3.14)

# 在这里填入你自己的编译器路径
# set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe  CACHE STRING "C compiler" FORCE)
# set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe  CACHE STRING "C++ compiler" FORCE)

project(RBC-Struct-Practice
        VERSION 2024
        LANGUAGES C CXX
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# People keep running CMake in the wrong folder, completely nuking their project or creating weird bugs.
# This checks if you're running CMake from a folder that already has CMakeLists.txt.
# Importantly, this catches the common case of running it from the root directory.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)

if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()

set(SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(THIRD_PARTY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

include_directories(${SRC_INCLUDE_DIR} ${THIRD_PARTY_INCLUDE_DIR})
include_directories(BEFORE src) # This is needed for gtest.


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(thirdparty)