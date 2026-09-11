cmake_minimum_required(VERSION 4.2)
project(mish)

set(CMAKE_CXX_STANDARD 23)

add_executable(mish main.cpp
        lexer.cpp
        lexer.h)

target_link_libraries(mish PRIVATE stdc++exp)