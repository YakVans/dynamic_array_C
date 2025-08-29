#include <stdlib.h>
#include "unity.h"

#include "tests_field_info.h"
#include "tests_dynamic_array.h"
#include "tests_sort.h"

void setUp(void) {};
void tearDown(void) {};

int main(void) {
    UNITY_BEGIN();
    run_fieldinfo_tests();
    run_da_tests();
    run_sort_tests();
    return UNITY_END();
}