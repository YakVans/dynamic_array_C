#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

#include "errors.h"
#include "field_info.h"

typedef struct DynamicArray{
    void *data;
    size_t size;
    size_t capacity;
    FieldInfo *field_info;
} DynamicArray;

ErrorCode dynamic_array_init(DynamicArray *arr, FieldInfo *field_info);
ErrorCode dynamic_array_add(DynamicArray *arr, const void *element);
ErrorCode dynamic_array_sort(DynamicArray *arr);
DAErrorPair dynamic_array_map(const DynamicArray *arr, void (*map_func)(const void*, void*));
DAErrorPair dynamic_array_where(const DynamicArray *arr, int (*where_func)(const void*));
ErrorCode dynamic_array_concat(DynamicArray *dest, const DynamicArray *src);
ErrorCode dynamic_array_print(const DynamicArray *arr);
ErrorCode dynamic_array_free(DynamicArray *arr);

#endif