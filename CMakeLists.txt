cmake_minimum_required(VERSION 3.13)
project(gdsl-c)

add_library(gdsl-c "")

add_subdirectory("src")
add_subdirectory("test")

set(MY_COMPILE_FLAGS -Wall -Wextra -pedantic)

target_compile_options(gdsl-c PRIVATE ${MY_COMPILE_FLAGS})

