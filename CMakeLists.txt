cmake_minimum_required(VERSION 3.15)

project(ingsock)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(third_party/catch2)

add_subdirectory(warning)
add_subdirectory(ingsock)
