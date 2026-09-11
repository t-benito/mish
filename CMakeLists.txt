cmake_minimum_required(VERSION 4.2)
project(Mish)

set(CMAKE_CXX_STANDARD 23)

add_executable(Mish main.cpp
        lexer.cpp
        lexer.h)

target_link_libraries(Mish PRIVATE stdc++exp)