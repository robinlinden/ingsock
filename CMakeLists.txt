cmake_minimum_required(VERSION 3.20)

project(ingsock)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(third_party/catch2)

# Warning setup

add_library(ingsock_warning INTERFACE)
add_library(ingsock::warning ALIAS ingsock_warning)

target_compile_options(ingsock_warning INTERFACE
    $<$<CXX_COMPILER_ID:Clang,GNU>:
        -Wall;
        -Wextra;
        -pedantic-errors;
        # = {0}; is a common idiom for initializing structs.
        -Wno-missing-field-initializers;
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        # TODO(robinlinden): /W4
        /W2;
    >
)

# Library

add_library(${PROJECT_NAME}
    ing/ingsock.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ingsock::warning
        $<$<PLATFORM_ID:Windows>:ws2_32>
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_20
)

# Testing

include(Catch)

add_executable(ingsock_test
    ing/ip_addr_v4_test.cpp
    ing/ip_addr_v6_test.cpp
    ing/socket_test.cpp
)

target_link_libraries(ingsock_test
    PRIVATE
        Catch2::Catch2WithMain
        ingsock
)

catch_discover_tests(ingsock_test)

add_subdirectory(example)
