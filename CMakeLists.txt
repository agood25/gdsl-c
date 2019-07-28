cmake_minimum_required(VERSION 3.13)
project(gdsl-c)

add_library(gdsl-c "")
add_executable(test-vec "")

add_subdirectory("src")
add_subdirectory("tests")

set(MY_COMPILE_FLAGS -Wall -Wextra)

target_compile_options(gdsl-c PRIVATE ${MY_COMPILE_FLAGS})
target_compile_options(test-vec PRIVATE ${MY_COMPILE_FLAGS})
target_link_libraries(test-vec PRIVATE gdsl-c)
