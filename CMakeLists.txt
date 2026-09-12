cmake_minimum_required(VERSION 4.2)
project(mish)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG        main
)

FetchContent_MakeAvailable(cli11)

add_executable(mish main.cpp
        lexer.cpp
        lexer.hpp
        error.cpp
        error.hpp
        parser.cpp
        parser.hpp)

target_link_libraries(mish PRIVATE CLI11::CLI11 stdc++exp)