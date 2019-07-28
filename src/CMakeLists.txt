target_sources(gdsl-c
    PUBLIC
        vector.c
        vector.h
)

target_sources(gdsl-c
    PRIVATE
        main.c
)

target_include_directories(test PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(test PRIVATE gdsl-c)
target_include_directories(gdsl-c PUBLIC ${CMAKE_CURRENT_LIST_DIR})

