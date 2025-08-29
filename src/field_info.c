#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "field_info.h"

static FieldInfo *INT_FIELD_INFO = NULL;
static FieldInfo *DOUBLE_FIELD_INFO = NULL;

static ErrorCode int_copy(void *dest, const void *src) {
    if (!dest || !src) return ERR_NULL_PTR;
    *(int*)dest = *(int*)src;
    return SUCCESS;
}

static ErrorCode int_free(void *element) {
    //не требуется для int
    return SUCCESS;
}

static IntErrorPair int_compare(const void *a, const void *b) {
    IntErrorPair int_error_pair = {0, SUCCESS};
    if (!a || !b) {
        int_error_pair.errorCode = ERR_NULL_PTR;
        return int_error_pair;
    }

    int ai = *(int*)a;
    int bi = *(int*)b;
    int_error_pair.result = (ai > bi) - (ai < bi);
    return int_error_pair;
}

static ErrorCode int_print(const void *element) {
    if (!element) return ERR_NULL_PTR;
    printf("%d", *(int*)element);
    return SUCCESS;
}


static ErrorCode double_copy(void *dest, const void *src) {
    if (!dest || !src) return ERR_NULL_PTR;
    *(double*)dest = *(double*)src;
    return SUCCESS;
}

static ErrorCode double_free(void *element) {
    //не требуется для double
    return SUCCESS;
}

static IntErrorPair double_compare(const void *a, const void *b) {
    IntErrorPair int_error_pair = {0, SUCCESS};
    if (!a || !b) {
        int_error_pair.errorCode = ERR_NULL_PTR;
        return int_error_pair;
    }
    
    const double EPSILON = 1e-10;
    double ai = *(double*)a;
    double bi = *(double*)b;
    
    if (fabs(ai - bi) < EPSILON) {
        int_error_pair.result = 0;
    }
    else {
        int_error_pair.result = (ai > bi) ? 1 : -1;
    }
    return int_error_pair;
}

static ErrorCode double_print(const void *element) {
    if (!element) return ERR_NULL_PTR;
    printf("%.2f", *(double*)element);
    return SUCCESS;
}

FieldInfo* GetIntFieldInfo(void) {
    if (INT_FIELD_INFO == NULL) {
        INT_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (INT_FIELD_INFO == NULL) {
            fprintf(stderr, "Memory allocation failed for INT_FIELD_INFO\n");
            exit(EXIT_FAILURE);
        }
        INT_FIELD_INFO->element_size = sizeof(int);
        INT_FIELD_INFO->copy = int_copy;
        INT_FIELD_INFO->free = int_free;
        INT_FIELD_INFO->compare = int_compare;
        INT_FIELD_INFO->print = int_print;
    }
    return INT_FIELD_INFO;
}

FieldInfo* GetDoubleFieldInfo(void) {
    if (DOUBLE_FIELD_INFO == NULL) {
        DOUBLE_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (DOUBLE_FIELD_INFO == NULL) {
            fprintf(stderr, "Memory allocation failed for DOUBLE_FIELD_INFO\n");
            exit(EXIT_FAILURE);
        }
        DOUBLE_FIELD_INFO->element_size = sizeof(double);
        DOUBLE_FIELD_INFO->copy = double_copy;
        DOUBLE_FIELD_INFO->free = double_free;
        DOUBLE_FIELD_INFO->compare = double_compare;
        DOUBLE_FIELD_INFO->print = double_print;
    }
    return DOUBLE_FIELD_INFO;
}