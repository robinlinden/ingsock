function(make_example name)
    set(tgt ingsock_${name})
    add_executable(${tgt} ${name}.cpp)
    target_link_libraries(${tgt} PRIVATE ingsock ingsock::warning)
endfunction()

make_example(client)
make_example(resolve)
make_example(server)
