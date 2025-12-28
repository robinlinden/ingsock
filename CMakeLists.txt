cmake_minimum_required(VERSION 3.15)

project(ingsock)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

enable_testing()

add_subdirectory(third_party/catch2)

add_subdirectory(warning)
add_subdirectory(ingsock)
