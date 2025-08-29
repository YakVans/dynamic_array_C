add_executable(tests_runner
    tests_runner.c
    tests_dynamic_array.c
    tests_field_info.c
    tests_sort.c
    ${CMAKE_SOURCE_DIR}/unity/unity.c
)

target_link_libraries(tests_runner PRIVATE src_lib)

target_include_directories(tests_runner PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/unity
)