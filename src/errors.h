#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

typedef struct DynamicArray DynamicArray;

typedef enum {
    SUCCESS,
    ERR_NULL_PTR,
    ERR_ALLOCATION_FAIL,
    ERR_TYPE_MISMATCH,
    ERR_INDEX_OUT_OF_BOUNDS,

    ERR_OVERFLOW_STR,
    ERR_NON_NUMERIC_INPUT,
    ERR_NUM_OVERFLOW,
    ERR_UNEXPECTED_INPUT_COUNT,

    UNKNOWN_ERROR
} ErrorCode;

void print_error(ErrorCode err);

typedef struct {
    int result;
    ErrorCode errorCode;
} IntErrorPair;

typedef struct {
    DynamicArray *result;
    ErrorCode errorCode;
} DAErrorPair;

#endif