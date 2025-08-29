#include <stdlib.h>
#include <stddef.h>
#define UNITY_INCLUDE_DOUBLE
#include "unity.h"

#include "tests_dynamic_array.h"
#include "field_info.h"
#include "dynamic_array.h"

void test_da_init_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    ErrorCode err = dynamic_array_init(arr, GetIntFieldInfo());

    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(0, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(0, arr->size);
    TEST_ASSERT_EQUAL_PTR(GetIntFieldInfo(), arr->field_info);

    dynamic_array_free(arr);
    free(arr);
}

void test_da_init_null(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    ErrorCode err;

    err = dynamic_array_init(arr, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    err = dynamic_array_init(NULL, GetIntFieldInfo());
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    err = dynamic_array_init(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    free(arr);
}


void test_da_free_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    ErrorCode err;
    
    err = dynamic_array_free(arr);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(0, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(0, arr->size);
    TEST_ASSERT_EQUAL_PTR(GetIntFieldInfo(), arr->field_info);

    free(arr);
}
void test_da_free_null(void) {
    ErrorCode err = dynamic_array_free(NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}
void test_da_free_double(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    ErrorCode err;
    
    dynamic_array_free(arr);
    err = dynamic_array_free(arr);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(0, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(0, arr->size);
    TEST_ASSERT_EQUAL_PTR(GetIntFieldInfo(), arr->field_info);

    free(arr);
}

void test_da_add_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    int a = 6, b = 8;
    ErrorCode err;

    err = dynamic_array_add(arr, &a);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NOT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(1, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(1, arr->size);
    TEST_ASSERT_EQUAL(6, ((int*)arr->data)[0]);

    err = dynamic_array_add(arr, &b);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NOT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(2, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(2, arr->size);
    TEST_ASSERT_EQUAL(6, ((int*)arr->data)[0]);
    TEST_ASSERT_EQUAL(8, ((int*)arr->data)[1]);

    for (int i = 0; i < 10; i++) {
        err = dynamic_array_add(arr, &i);
        TEST_ASSERT_EQUAL(SUCCESS, err);
    }
    
    TEST_ASSERT_NOT_NULL(arr->data);
    TEST_ASSERT_EQUAL(16, arr->capacity);
    TEST_ASSERT_EQUAL(12, arr->size);
    
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL(i, ((int*)arr->data)[i + 2]);
    }
    
    dynamic_array_free(arr);
    free(arr);
}
void test_da_add_null(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    int values[] = {7, 5, 2};
    dynamic_array_init(arr, GetIntFieldInfo());
    dynamic_array_add(arr, &values[1]);
    dynamic_array_add(arr, &values[2]);
    ErrorCode err;

    err = dynamic_array_add(NULL, &values[0]);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    TEST_ASSERT_EQUAL(7, values[0]);

    err = dynamic_array_add(arr, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    TEST_ASSERT_EQUAL(5, ((int*)arr->data)[0]);
    TEST_ASSERT_EQUAL(2, ((int*)arr->data)[1]);
    TEST_ASSERT_EQUAL(2, arr->size);

    err = dynamic_array_add(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    dynamic_array_free(arr);
    free(arr);
}

void test_da_sort_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    ErrorCode err;

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 11; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    err = dynamic_array_sort(arr);

    TEST_ASSERT_EQUAL(SUCCESS, err);
    int sorted_values[] = {-12, -3, -2, 0, 1, 5, 5, 6, 7, 9, 12};
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(sorted_values[i], ((int*)arr->data)[i]);
    }

    dynamic_array_free(arr);
    free(arr);
}
void test_da_sort_empty(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    ErrorCode err;

    err = dynamic_array_sort(arr);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(0, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(0, arr->size);

    dynamic_array_free(arr);
    free(arr);
}
void test_da_sort_single(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    int value = 6;
    dynamic_array_add(arr, &value);
    ErrorCode err;

    err = dynamic_array_sort(arr);
    
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NOT_NULL(arr->data);
    TEST_ASSERT_EQUAL_UINT(1, arr->capacity);
    TEST_ASSERT_EQUAL_UINT(1, arr->size);
    TEST_ASSERT_EQUAL(6, ((int*)arr->data)[0]);

    dynamic_array_free(arr);
    free(arr);
}
void test_da_sort_null(void) {
    ErrorCode err = dynamic_array_sort(NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}

void int_double(const void *src, void *dest) {
    *(int*)dest = *(int*)src * 2;
}
void test_da_map_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    DAErrorPair mapped_arr = {malloc(sizeof(DynamicArray)), SUCCESS};
    dynamic_array_init(mapped_arr.result, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 11; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    mapped_arr = dynamic_array_map(arr, &int_double);

    TEST_ASSERT_EQUAL(SUCCESS, mapped_arr.errorCode);
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
        TEST_ASSERT_EQUAL(values[i]*2, ((int*)mapped_arr.result->data)[i]);
    }

    dynamic_array_free(arr);
    free(arr);
    dynamic_array_free(mapped_arr.result);
    free(mapped_arr.result);
}
void test_da_map_empty(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    DAErrorPair mapped_arr = {malloc(sizeof(DynamicArray)), SUCCESS};
    dynamic_array_init(mapped_arr.result, GetIntFieldInfo());

    mapped_arr = dynamic_array_map(arr, &int_double);

    TEST_ASSERT_EQUAL(SUCCESS, mapped_arr.errorCode);
    TEST_ASSERT_NULL(arr->data);
    TEST_ASSERT_NULL(mapped_arr.result->data);

    dynamic_array_free(arr);
    free(arr);
    dynamic_array_free(mapped_arr.result);
    free(mapped_arr.result);
}
void test_da_map_null(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    DAErrorPair mapped_arr = {malloc(sizeof(DynamicArray)), SUCCESS};
    dynamic_array_init(mapped_arr.result, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 11; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    mapped_arr = dynamic_array_map(arr, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, mapped_arr.errorCode);
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }

    mapped_arr = dynamic_array_map(NULL, int_double);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, mapped_arr.errorCode);

    mapped_arr = dynamic_array_map(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, mapped_arr.errorCode);

    dynamic_array_free(arr);
    free(arr);
    dynamic_array_free(mapped_arr.result);
    free(mapped_arr.result);
}

int int_greater_5(const void *element) {
    return *(int*)element > 5;
}
void test_da_where_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    DAErrorPair filtered_arr = {malloc(sizeof(DynamicArray)), SUCCESS};
    dynamic_array_init(filtered_arr.result, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 11; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    filtered_arr = dynamic_array_where(arr, int_greater_5);

    int filtered_values[] = {9, 7, 12, 6};
    TEST_ASSERT_EQUAL(SUCCESS, filtered_arr.errorCode);
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(filtered_values[i], ((int*)filtered_arr.result->data)[i]);
    }

    dynamic_array_free(arr);
    free(arr);
    dynamic_array_free(filtered_arr.result);
    free(filtered_arr.result);
}
void test_da_where_empty(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    DAErrorPair filtered_arr = {malloc(sizeof(DynamicArray)), SUCCESS};
    dynamic_array_init(filtered_arr.result, GetIntFieldInfo());

    filtered_arr = dynamic_array_where(arr, int_greater_5);

    TEST_ASSERT_EQUAL(SUCCESS, filtered_arr.errorCode);
    TEST_ASSERT_NULL(arr->data);
    TEST_ASSERT_NULL(filtered_arr.result->data);

    dynamic_array_free(arr);
    free(arr);
    dynamic_array_free(filtered_arr.result);
    free(filtered_arr.result);
}
void test_da_where_null(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    dynamic_array_init(arr, GetIntFieldInfo());
    DAErrorPair filtered_arr = {malloc(sizeof(DynamicArray)), SUCCESS};
    dynamic_array_init(filtered_arr.result, GetIntFieldInfo());

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 11; i++) {
        dynamic_array_add(arr, &values[i]);
    }

    filtered_arr = dynamic_array_where(arr, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, filtered_arr.errorCode);
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)arr->data)[i]);
    }
    
    filtered_arr = dynamic_array_where(NULL, int_greater_5);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, filtered_arr.errorCode);
    
    filtered_arr = dynamic_array_where(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, filtered_arr.errorCode);

    dynamic_array_free(arr);
    free(arr);
    dynamic_array_free(filtered_arr.result);
    free(filtered_arr.result);
}

void test_da_concat_base(void) {
    DynamicArray *left = malloc(sizeof(DynamicArray));
    dynamic_array_init(left, GetIntFieldInfo());
    DynamicArray *right = malloc(sizeof(DynamicArray));
    dynamic_array_init(right, GetIntFieldInfo());
    ErrorCode err;

    int values[] = {9, 7, 12, 5, -12, 5, 6, -2, 1, -3, 0};
    for (int i = 0; i < 6; i++) {
        dynamic_array_add(left, &values[i]);
    }
    for (int i = 6; i < 11; i++) {
        dynamic_array_add(right, &values[i]);
    }

    err = dynamic_array_concat(left, right);

    TEST_ASSERT_EQUAL(SUCCESS, err);
    for (int i = 0; i < 11; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)left->data)[i]);
    }
    for (int i = 6; i < 11; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)right->data)[i - 6]);
    }

    dynamic_array_free(left);
    free(left);
    dynamic_array_free(right);
    free(right);
}
void test_da_concat_empty(void) {
    DynamicArray *left = malloc(sizeof(DynamicArray));
    dynamic_array_init(left, GetIntFieldInfo());
    DynamicArray *right = malloc(sizeof(DynamicArray));
    dynamic_array_init(right, GetIntFieldInfo());
    ErrorCode err;
    
    int values[] = {9, -5, 2};
    for (int i = 0; i < 3; i++) {
        dynamic_array_add(left, &values[i]);
    }

    err = dynamic_array_concat(left, right);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)left->data)[i]);
    }
    TEST_ASSERT_NULL(right->data);

    err = dynamic_array_concat(right, right);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NULL(right->data);

    err = dynamic_array_concat(right, left);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(values[i], ((int*)left->data)[i]);
        TEST_ASSERT_EQUAL(values[i], ((int*)right->data)[i]);
    }

    dynamic_array_free(left);
    free(left);
    dynamic_array_free(right);
    free(right);
}
void test_da_concat_diff_types(void) {
    DynamicArray *left = malloc(sizeof(DynamicArray));
    dynamic_array_init(left, GetIntFieldInfo());
    DynamicArray *right = malloc(sizeof(DynamicArray));
    dynamic_array_init(right, GetDoubleFieldInfo());
    ErrorCode err;

    int valuei[] = {9, -5, 2};
    for (int i = 0; i < 3; i++) {
        dynamic_array_add(left, &valuei[i]);
    }
    double valued[] = {6.32, -0.4};
    for (int i = 0; i < 2; i++) {
        dynamic_array_add(right, &valued[i]);
    }

    err = dynamic_array_concat(left, right);

    TEST_ASSERT_EQUAL(ERR_TYPE_MISMATCH, err);
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(valuei[i], ((int*)left->data)[i]);
    }
    for (int i = 0; i < 2; i++) {
        TEST_ASSERT_DOUBLE_WITHIN(1e-10, valued[i], ((double*)right->data)[i]);
    }

    dynamic_array_free(left);
    free(left);
    dynamic_array_free(right);
    free(right);
}
void test_da_concat_null(void) {
    DynamicArray *left = malloc(sizeof(DynamicArray));
    dynamic_array_init(left, GetIntFieldInfo());
    DynamicArray *right = malloc(sizeof(DynamicArray));
    dynamic_array_init(right, GetDoubleFieldInfo());
    ErrorCode err;
    
    int values1[] = {9, -5, 2};
    for (int i = 0; i < 3; i++) {
        dynamic_array_add(left, &values1[i]);
    }
    int values2[] = {6, -1};
    for (int i = 0; i < 2; i++) {
        dynamic_array_add(right, &values2[i]);
    }

    err = dynamic_array_concat(left, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(values1[i], ((int*)left->data)[i]);
    }

    err = dynamic_array_concat(NULL, right);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    for (int i = 0; i < 2; i++) {
        TEST_ASSERT_EQUAL(values2[i], ((int*)right->data)[i]);
    }

    err = dynamic_array_concat(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    dynamic_array_free(left);
    free(left);
    dynamic_array_free(right);
    free(right);
}

void test_da_print_base(void) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    int values[] = {5, 7, 2};
    dynamic_array_init(arr, GetIntFieldInfo());
    dynamic_array_add(arr, &values[0]);
    dynamic_array_add(arr, &values[1]);
    dynamic_array_add(arr, &values[2]);
    ErrorCode err;

    err = dynamic_array_print(arr);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_NOT_NULL(arr->data);
    TEST_ASSERT_EQUAL(3, arr->size);
    TEST_ASSERT_EQUAL(4, arr->capacity);
    TEST_ASSERT_EQUAL(5, ((int*)arr->data)[0]);
    TEST_ASSERT_EQUAL(7, ((int*)arr->data)[1]);
    TEST_ASSERT_EQUAL(2, ((int*)arr->data)[2]);

    dynamic_array_free(arr);
    free(arr);
}
void test_da_print_null(void) {
    ErrorCode err = dynamic_array_print(NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}

void run_da_tests(void) {
    RUN_TEST(test_da_init_base);
    RUN_TEST(test_da_init_null);
    
    RUN_TEST(test_da_free_base);
    RUN_TEST(test_da_free_null);
    RUN_TEST(test_da_free_double);
    
    RUN_TEST(test_da_add_base);
    RUN_TEST(test_da_add_null);

    RUN_TEST(test_da_sort_base);
    RUN_TEST(test_da_sort_empty);
    RUN_TEST(test_da_sort_single);
    RUN_TEST(test_da_sort_null);

    RUN_TEST(test_da_map_base);
    RUN_TEST(test_da_map_empty);
    RUN_TEST(test_da_map_null);
    
    RUN_TEST(test_da_where_base);
    RUN_TEST(test_da_where_empty);
    RUN_TEST(test_da_where_null);

    RUN_TEST(test_da_concat_base);
    RUN_TEST(test_da_concat_empty);
    RUN_TEST(test_da_concat_diff_types);
    RUN_TEST(test_da_concat_null);
    
    RUN_TEST(test_da_print_base);
    RUN_TEST(test_da_print_null);
}
