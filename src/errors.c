#include <stdio.h>

#include "errors.h"

void print_error(ErrorCode err) {
    switch (err) {
        case SUCCESS: {
            break;
        }

        case ERR_NULL_PTR: {
            printf("Error: null pointer\n");
            break;
        }
        case ERR_ALLOCATION_FAIL: {
            printf("Error: allocation fail\n");
            break;
        }
        case ERR_TYPE_MISMATCH: {
            printf("Error: type mismatch\n");
            break;
        }
        case ERR_INDEX_OUT_OF_BOUNDS: {
            printf("Error: index out of bounds\n");
            break;
        }

        case ERR_OVERFLOW_STR: {
            printf("Error: string is too big\n");
            break;
        }
        case ERR_NON_NUMERIC_INPUT: {
            printf("Error: non-numeric characters detected\n");
            break;
        }
        case ERR_NUM_OVERFLOW: {
            printf("Error: number is too big/small\n");
            break;
        }
        case ERR_UNEXPECTED_INPUT_COUNT: {
            printf("Error: count of numbers is not expected\n");
            break;
        }

        default: {
            printf("Error: unknown error\n");
            break;
        }
    }
}