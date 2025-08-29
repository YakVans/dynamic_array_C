add_library(src_lib STATIC 
    field_info.c
    sort.c
    dynamic_array.c
    manual_read.c
    errors.c)

target_include_directories(src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
