#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#define UNITY_INCLUDE_DOUBLE
#include "unity.h"

#include "tests_field_info.h"
#include "field_info.h"

void test_int_copy_base(void) {
    FieldInfo *field_info = GetIntFieldInfo();
    int src = 5, dest = 3;

    ErrorCode err = field_info->copy(&dest, &src);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(5, dest);
    TEST_ASSERT_EQUAL(5, src);
}
void test_int_copy_null(void) {
    FieldInfo *field_info = GetIntFieldInfo();
    int src = 5;
    ErrorCode err;

    err = field_info->copy(NULL, &src);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    TEST_ASSERT_EQUAL(5, src);
    
    err = field_info->copy(&src, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    
    err = field_info->copy(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}
void test_int_copy_same(void) {
    FieldInfo *field_info = GetIntFieldInfo();
    int src = 5;

    ErrorCode err = field_info->copy(&src, &src);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(5, src);
}

void test_int_compare_base(void) {
    FieldInfo *field_info = GetIntFieldInfo();
    int a = 5, b = 3, c = 5;
    IntErrorPair res;

    res = field_info->compare(&b, &a);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(-1, res.result);

    res = field_info->compare(&a, &b);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(1, res.result);

    res = field_info->compare(&c, &a);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(0, res.result);
}
void test_int_compare_null(void) {
    FieldInfo *field_info = GetIntFieldInfo();
    int a = 5;
    IntErrorPair res;

    res = field_info->compare(NULL, &a);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, res.errorCode);

    res = field_info->compare(&a, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, res.errorCode);

    res = field_info->compare(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, res.errorCode);
}

void test_int_print(void) {
    FieldInfo *field_info = GetIntFieldInfo();
    int src = 5;
    ErrorCode err;

    err = field_info->print(&src);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_EQUAL(5, src);

    err = field_info->print(NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    putchar('\n');
}


void test_double_copy_base(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    const double EPSILON = 1e-10;
    double src = 5.69, dest = 3.14;

    ErrorCode err = field_info->copy(&dest, &src);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_DOUBLE_WITHIN(EPSILON, 5.69, dest);
    TEST_ASSERT_DOUBLE_WITHIN(EPSILON, 5.69, src);
}
void test_double_copy_null(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    const double EPSILON = 1e-10;
    double src = 5.69;
    ErrorCode err;

    err = field_info->copy(NULL, &src);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    TEST_ASSERT_DOUBLE_WITHIN(EPSILON, 5.69, src);
    
    err = field_info->copy(&src, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
    
    err = field_info->copy(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);
}
void test_double_copy_same(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    const double EPSILON = 1e-10;
    double src = 5.69;

    ErrorCode err = field_info->copy(&src, &src);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_DOUBLE_WITHIN(EPSILON, 5.69, src);
}

void test_double_compare_base(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    double a = 5.69, b = 3.14, c = 5.69;
    IntErrorPair res;

    res = field_info->compare(&b, &a);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(-1, res.result);

    res = field_info->compare(&a, &b);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(1, res.result);

    res = field_info->compare(&c, &a);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(0, res.result);
}
void test_double_compare_epsilon(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    const double EPSILON = 1e-10;
    double a = 1.0, b = 1.0 + EPSILON / 2, c = 1.0 + EPSILON * 2;
    IntErrorPair res;

    res = field_info->compare(&b, &a);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(0, res.result);

    res = field_info->compare(&c, &a);
    TEST_ASSERT_EQUAL(SUCCESS, res.errorCode);
    TEST_ASSERT_EQUAL(1, res.result);
}
void test_double_compare_null(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    double a = 5.69;
    IntErrorPair res;

    res = field_info->compare(NULL, &a);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, res.errorCode);

    res = field_info->compare(&a, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, res.errorCode);

    res = field_info->compare(NULL, NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, res.errorCode);
}

void test_double_print(void) {
    FieldInfo *field_info = GetDoubleFieldInfo();
    const double EPSILON = 1e-10;
    double src = 5.69;
    ErrorCode err;

    err = field_info->print(&src);
    TEST_ASSERT_EQUAL(SUCCESS, err);
    TEST_ASSERT_DOUBLE_WITHIN(EPSILON, 5.69, src);

    err = field_info->print(NULL);
    TEST_ASSERT_EQUAL(ERR_NULL_PTR, err);

    putchar('\n');
}


void run_fieldinfo_tests(void) {
    RUN_TEST(test_int_copy_base);
    RUN_TEST(test_int_copy_null);
    RUN_TEST(test_int_copy_same);

    RUN_TEST(test_int_compare_base);
    RUN_TEST(test_int_compare_null);

    RUN_TEST(test_int_print);


    RUN_TEST(test_double_copy_base);
    RUN_TEST(test_double_copy_null);
    RUN_TEST(test_double_copy_same);

    RUN_TEST(test_double_compare_base);
    RUN_TEST(test_double_compare_epsilon);
    RUN_TEST(test_double_compare_null);

    RUN_TEST(test_double_print);
}