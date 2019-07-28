target_sources(test-vec
    PRIVATE
        test-vec.c
)

target_include_directories(test-vec 
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR} 
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(test-vec 
    PRIVATE
        check 
        -lcheck_pic 
        -pthread 
        -lrt 
        -lm 
        -lsubunit)
        
target_compile_options(test-vec PRIVATE -pthread)
