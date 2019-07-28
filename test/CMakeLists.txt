target_sources(test-vec
    PRIVATE
        test-vec.c
)

target_include_directories(test-vec PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_SOURCE_DIR}/src)

