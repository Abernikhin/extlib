add_executable(test main.c)

add_library(extlib STATIC
    memory.c
    collections.c
)

target_link_libraries(test PUBLIC extlib)
