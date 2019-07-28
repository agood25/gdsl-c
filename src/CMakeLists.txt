target_sources(gdsl-c
    PUBLIC
        vector.c
        vector.h
)

target_include_directories(gdsl-c PUBLIC ${CMAKE_CURRENT_LIST_DIR})

