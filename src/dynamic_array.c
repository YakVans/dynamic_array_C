#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "dynamic_array.h"
#include "sort.h"

ErrorCode dynamic_array_init(DynamicArray *arr, FieldInfo *field_info) {
    if (!arr || !field_info) return ERR_NULL_PTR;

    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
    arr->field_info = field_info;

    return SUCCESS;
}

ErrorCode dynamic_array_free(DynamicArray *arr) {
    if (!arr) return ERR_NULL_PTR;

    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;

    return SUCCESS;
}

ErrorCode dynamic_array_add(DynamicArray *arr, const void *element) {
    if (!arr || !element) return ERR_NULL_PTR;

    if (arr->size >= arr->capacity) {
        arr->capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;
        arr->data = realloc(arr->data, arr->capacity * arr->field_info->element_size);
        if (arr->data == NULL) return ERR_ALLOCATION_FAIL;
    }

    void *dest = (char*)arr->data + arr->size * arr->field_info->element_size;
    ErrorCode errorCode = arr->field_info->copy(dest, element);
    if (errorCode != SUCCESS) return errorCode;
    arr->size++;

    return SUCCESS;
}

ErrorCode dynamic_array_sort(DynamicArray *arr) {
    if (!arr) return ERR_NULL_PTR;
    if (arr->size < 2) return SUCCESS;
    return quicksort(arr, 0, arr->size - 1);
}

DAErrorPair dynamic_array_map(const DynamicArray *arr, void (*map_func)(const void*, void*)) {
    DAErrorPair DA_error_pair = {NULL, SUCCESS};
    if (!arr || !map_func) {
        DA_error_pair.errorCode = ERR_NULL_PTR;
        return DA_error_pair;
    }

    DynamicArray *mapped_arr = malloc(sizeof(DynamicArray));
    if (!mapped_arr) {
        DA_error_pair.errorCode = ERR_ALLOCATION_FAIL;
        return DA_error_pair;
    }
    dynamic_array_init(mapped_arr, arr->field_info);

    void *dest = malloc(arr->field_info->element_size);
    if (!dest) {
        DA_error_pair.errorCode = ERR_ALLOCATION_FAIL;
        return DA_error_pair;
    }
    for (size_t i = 0; i < arr->size; i++) {
        void *src = (char*)arr->data + i * arr->field_info->element_size;
        map_func(src, dest);
        ErrorCode add_result = dynamic_array_add(mapped_arr, dest);

        if (add_result != SUCCESS) {
            DA_error_pair.errorCode = add_result;
            return DA_error_pair;
        }
    }
    free(dest);

    DA_error_pair.result = mapped_arr;
    return DA_error_pair;
}

DAErrorPair dynamic_array_where(const DynamicArray *arr, int (*where_func)(const void*)) {
    DAErrorPair DA_error_pair = {NULL, SUCCESS};
    if (!arr || !where_func) {
        DA_error_pair.errorCode = ERR_NULL_PTR;
        return DA_error_pair;
    }

    DynamicArray *filtered_arr = malloc(sizeof(DynamicArray));
    if (!filtered_arr) {
        DA_error_pair.errorCode = ERR_ALLOCATION_FAIL;
        return DA_error_pair;
    }

    dynamic_array_init(filtered_arr, arr->field_info);
    for (size_t i = 0; i < arr->size; i++) {
        void *element = (char*)arr->data + i * arr->field_info->element_size;
        if (where_func(element)) {
            ErrorCode add_result = dynamic_array_add(filtered_arr, element);

            if (add_result != SUCCESS) {
                DA_error_pair.errorCode = add_result;
                return DA_error_pair;
            }
        }
    }

    DA_error_pair.result = filtered_arr;
    return DA_error_pair;
}

ErrorCode dynamic_array_concat(DynamicArray *dest, const DynamicArray *src) {
    if (!dest || !src) return ERR_NULL_PTR;
    if (dest->field_info != src->field_info) return ERR_TYPE_MISMATCH;

    for (size_t i = 0; i < src->size; i++) {
        void *element = (char*)src->data + i * src->field_info->element_size;
        ErrorCode errorCode = dynamic_array_add(dest, element);
        if (errorCode != SUCCESS) return errorCode;
    }

    return SUCCESS;
}

ErrorCode dynamic_array_print(const DynamicArray *arr) {
    if (!arr) return ERR_NULL_PTR;

    printf("[");
    for (size_t i = 0; i < arr->size; i++) {
        void *element = (char*)arr->data + i * arr->field_info->element_size;
        ErrorCode errorCode = arr->field_info->print(element);
        if (errorCode != SUCCESS) return errorCode;
        if (i < arr->size - 1) printf(", ");
    }
    printf("]\n");
    
    return SUCCESS;
}
