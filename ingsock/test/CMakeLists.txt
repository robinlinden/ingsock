include(Catch)

project(test_ingsock)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/test_ip_addr_v4.cpp
    src/test_ip_addr_v6.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Catch2::Catch2
        ingsock
)

catch_discover_tests(${PROJECT_NAME})
