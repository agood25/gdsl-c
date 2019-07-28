target_sources(gdsl-c
    PUBLIC
        vector.c
        vector.h
        ds_def.h
)

target_include_directories(gdsl-c PUBLIC ${CMAKE_CURRENT_LIST_DIR})

