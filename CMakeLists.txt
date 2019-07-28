cmake_minimum_required(VERSION 3.13)
project(gdsl-c)

add_library(gdsl-c "")
add_executable(test "")

add_subdirectory("src")

target_compile_options(gdsl-c PRIVATE -Wall -Wextra)