project(ingsock)

add_library(${PROJECT_NAME}
    src/ingsock.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
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

add_subdirectory(example)
add_subdirectory(test)
