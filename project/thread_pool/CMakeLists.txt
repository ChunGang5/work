cmake_minimum_required(VERSION 3.5)

project(thread_pool)

# 添加C++11支持
set(CMAKE_CXX_STANDARD 11)

# 添加源文件
add_executable(thread_pool main.cpp)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
