project(ingsock_warning)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ingsock::warning ALIAS ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} INTERFACE
    $<$<CXX_COMPILER_ID:Clang,GNU>:
        -Wall;
        -Wextra;
        -Werror;
        -pedantic-errors;
        # = {0}; is a common idiom for initializing structs.
        -Wno-missing-field-initializers;
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        # TODO(robinlinden): /W4
        /W2;
        /WX;
    >
)
