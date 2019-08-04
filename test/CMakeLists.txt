function(generate_test_executable NAME)
    add_executable(test-${NAME} "")
    
    target_sources(test-${NAME}
        PRIVATE
            test-${NAME}.c
    )

    target_include_directories(test-${NAME}
        PRIVATE 
            ${CMAKE_CURRENT_LIST_DIR} 
            ${CMAKE_SOURCE_DIR}/src
    )

    target_link_libraries(test-${NAME} 
        PRIVATE
            check 
            -lcheck_pic 
            -pthread 
            -lrt 
            -lm 
            -lsubunit)
            
    target_compile_options(test-${NAME} PRIVATE -pthread)

    target_compile_options(test-${NAME} PRIVATE ${MY_COMPILE_FLAGS})
    target_link_libraries(test-${NAME} PRIVATE gdsl-c)

endfunction(generate_test_executable)

generate_test_executable(stack)
generate_test_executable(vec)
generate_test_executable(hashmap)


