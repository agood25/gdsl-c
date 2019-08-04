target_sources(gdsl-c
    PUBLIC
        gdsl_def.h
        hashmap.c
        hashmap.h
        stack.c
        stack.h
        vector.c
        vector.h
)

target_include_directories(gdsl-c PUBLIC ${CMAKE_CURRENT_LIST_DIR})

