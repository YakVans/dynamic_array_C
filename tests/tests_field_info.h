#ifndef TESTS_FIELD_INFO_H
#define TESTS_FIELD_INFO_H

void test_int_copy_base(void);
void test_int_copy_null(void);
void test_int_copy_same(void);
void test_int_compare_base(void);
void test_int_compare_null(void);
void test_int_print(void);

void test_double_copy_base(void);
void test_double_copy_null(void);
void test_double_copy_same(void);
void test_double_compare_base(void);
void test_double_compare_epsilon(void);
void test_double_compare_null(void);
void test_double_print(void);

void run_fieldinfo_tests(void);

#endif