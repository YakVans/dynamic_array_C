cmake_minimum_required(VERSION 3.10)
project(lab_1 C)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(main main.c)

target_link_libraries(main PUBLIC src_lib)
