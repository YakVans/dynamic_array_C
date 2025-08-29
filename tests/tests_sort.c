#include <stdlib.h>
#include <stddef.h>
#include "unity.h"

#include "tests_sort.h"
#include "sort.h"
#include "field_info.h"
#include "dynamic_array.h"

void test_swap_base(void) {
    int a, b, c = 4, d = -9;
    FieldInfo *field_info = GetIntFieldInfo();
    field_info->copy(&a, &c);
    field_info->copy(&b, &d);
    ErrorCode err;

    err = swap(&a, &b, field_info);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(4, b);
    TEST_ASSERT_EQUAL(-9, a);
}
void test_swap_null(void) {
    int a, b, c = 4, d = -9;
    FieldInfo *field_info = GetIntFieldInfo();
    field_info->copy(&a, &c);
    field_info->copy(&b, &d);
    ErrorCode err;

    err = swap(&a, &b, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    
    err = swap(&a, NULL, field_info);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    err = swap(NULL, &b, field_info);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    err = swap(&a, NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    
    err = swap(NULL, &b, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    
    err = swap(NULL, NULL, field_info);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    err = swap(NULL, NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}

void test_quicksort_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 11; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    ErrorCode err = quicksort(arr, 0, arr->size - 1);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(11, arr->size);
    TEST_ASSERT_EQUAL(16, arr->capacity);

    int sorted_values[] = {-12, -3, -2, 0, 1, 5, 5, 6, 7, 9, 12};
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(sorted_values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_empty(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    ErrorCode err = quicksort(arr, 0, 0);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(0, arr->size);
    TEST_ASSERT_EQUAL(0, arr->capacity);
    TEST_ASSERT_NULL(arr->data);

    free(arr);
}
void test_quicksort_single(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int element = 3;
    dynamic_array_add(arr, &element);

    ErrorCode err = quicksort(arr, 0, arr->size - 1);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(1, arr->size);
    TEST_ASSERT_EQUAL(1, arr->capacity);
    TEST_ASSERT_EQUAL(3, *(int*)arr->data);

    free(arr);
}
void test_quicksort_low_equal_high(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5};
    for (int i = 0; i < 4; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    ErrorCode err = quicksort(arr, 2, 2);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);

    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_low_greater_high(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5};
    for (int i = 0; i < 4; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    ErrorCode err = quicksort(arr, 3, 1);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);

    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_low_less_zero(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5};
    for (int i = 0; i < 4; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    ErrorCode err = quicksort(arr, -1, 2);
    
    TEST_ASSERT_EQUAL(ERR_INDEX_OUT_OF_BOUNDS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);
    
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_high_greater_size(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5};
    for (int i = 0; i < 4; i++) {
        dynamic_array_add(arr, &values[i]);
    }
    
    ErrorCode err = quicksort(arr, 1, 6);
    
    TEST_ASSERT_EQUAL(ERR_INDEX_OUT_OF_BOUNDS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);
    
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_sorted(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {5, 7, 9, 12};
    for (int i = 0; i < 4; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    ErrorCode err = quicksort(arr, 0, arr->size - 1);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);
    
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_sorted_reverse(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int values[] = {5, 7, 9, 12};
    for (int i = 3; i >= 0; i--) {
        dynamic_array_add(arr, &values[i]);
    }

    ErrorCode err = quicksort(arr, 0, arr->size - 1);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);
    
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_each_same(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());

    int element = 3;
    for (int i = 0; i < 4; i++) {
        dynamic_array_add(arr, &element);
    }

    ErrorCode err = quicksort(arr, 0, arr->size - 1);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(4, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);
    
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(3, ((int*)arr->data)[i]);
    }

    free(arr);
}
void test_quicksort_null(void) {
    ErrorCode err = quicksort(NULL, 0, 0);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}

void run_sort_tests(void) {
    RUN_TEST(test_swap_base);
    RUN_TEST(test_swap_null);
    
    RUN_TEST(test_quicksort_base);
    RUN_TEST(test_quicksort_empty);
    RUN_TEST(test_quicksort_single);
    RUN_TEST(test_quicksort_low_equal_high);
    RUN_TEST(test_quicksort_low_greater_high);
    RUN_TEST(test_quicksort_low_less_zero);
    RUN_TEST(test_quicksort_high_greater_size);
    RUN_TEST(test_quicksort_sorted);
    RUN_TEST(test_quicksort_sorted_reverse);
    RUN_TEST(test_quicksort_each_same);
    RUN_TEST(test_quicksort_null);
}