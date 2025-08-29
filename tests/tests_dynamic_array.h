#ifndef TESTS_DYNAMIC_ARRAY_H
#define TESTS_DYNAMIC_ARRAY_H

void test_da_init_base(void);
void test_da_init_null(void);

void test_da_free_base(void);
void test_da_free_null(void);
void test_da_free_double(void);

void test_da_add_base(void);
void test_da_add_null(void);

void test_da_sort_base(void);
void test_da_sort_empty(void);
void test_da_sort_single(void);
void test_da_sort_null(void);

void int_double(const void *src, void *dest);
void test_da_map_base(void);
void test_da_map_empty(void);
void test_da_map_null(void);

int int_greater_5(const void *element);
void test_da_where_base(void);
void test_da_where_empty(void);
void test_da_where_null(void);

void test_da_concat_base(void);
void test_da_concat_empty(void);
void test_da_concat_diff_types(void);
void test_da_concat_null(void);

void test_da_print_base(void);
void test_da_print_null(void);

void run_da_tests(void);

#endif