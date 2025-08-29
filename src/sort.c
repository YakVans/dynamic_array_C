#include <stdlib.h>

#include "sort.h"
#include "errors.h"

ErrorCode swap(void *a, void *b, FieldInfo *field_info) {
    if (!a || !b || !field_info) return ERR_NULL_PTR;
    void *c = malloc(field_info->element_size);
    if (!c) return ERR_ALLOCATION_FAIL;

    ErrorCode err;
    err = field_info->copy(c, a);
    if (err != SUCCESS) {
        free(c);
        return err;
    }

    err = field_info->copy(a, b);
    if (err != SUCCESS) {
        free(c);
        return err;
    }

    err = field_info->copy(b, c);
    if (err != SUCCESS) {
        free(c);
        return err;
    }

    free(c);
    return SUCCESS;
}

ErrorCode quicksort(DynamicArray *arr, int low, int high) {
    if (!arr) return ERR_NULL_PTR;
    if (low >= high) return SUCCESS;
    if (low < 0 || high >= arr->size) return ERR_INDEX_OUT_OF_BOUNDS;
    ErrorCode err;

    int pivot = (low + high) / 2;
    int left = low;
    int right = high;
    while (left <= right) {
        IntErrorPair int_err;
        do {
            int_err = arr->field_info->compare(\
                ((char*)arr->data + arr->field_info->element_size * left),\
                ((char*)arr->data + arr->field_info->element_size * pivot));
            if (int_err.errorCode != SUCCESS) return int_err.errorCode;
            if (int_err.result < 0) left++;
        } while (int_err.result < 0);

        do {
            int_err = arr->field_info->compare(\
                ((char*)arr->data + arr->field_info->element_size * right),\
                ((char*)arr->data + arr->field_info->element_size * pivot));
            if (int_err.errorCode != SUCCESS) return int_err.errorCode;
            if (int_err.result > 0) right--;
        } while (int_err.result > 0);

        if (left <= right) {
            err = swap(((char*)arr->data + arr->field_info->element_size * left),\
                ((char*)arr->data + arr->field_info->element_size * right), arr->field_info);
            if (err != SUCCESS) return err;

            if (pivot == left) pivot = right;
            else if (pivot == right) pivot = left;
            left ++;
            right --;
        }
    }

    if (low < right) {
        err = quicksort(arr, low, right);
        if (err != SUCCESS) return err;
    }
    
    if (left < high) {
        err = quicksort(arr, left, high);
        if (err != SUCCESS) return err;
    }

    return SUCCESS;
}