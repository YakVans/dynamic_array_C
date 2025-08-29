#ifndef TESTS_SORT_H
#define TESTS_SORT_H

void test_swap_base(void);
void test_swap_null(void);

void test_quicksort_base(void);
void test_quicksort_empty(void);
void test_quicksort_single(void);
void test_quicksort_low_equal_high(void);
void test_quicksort_low_greater_high(void);
void test_quicksort_low_less_zero(void);
void test_quicksort_high_greater_size(void);
void test_quicksort_sorted(void);
void test_quicksort_sorted_reverse(void);
void test_quicksort_each_same(void);
void test_quicksort_null(void);

void run_sort_tests(void);

#endif