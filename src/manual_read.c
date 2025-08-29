#include "manual_read.h"
#include "errors.h"
#include "dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>


char *my_getline(size_t size) {
    char *buffer = malloc(size);
    int c;
    size_t len = 0;
    while (len < size - 1) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        buffer[len] = c;
        len++;
    }
    buffer[len] = '\0';
    return buffer;
}

DynamicArray* string_to_values_int(const char* str, ErrorCode *err) {
    DynamicArray* arr = malloc(sizeof(DynamicArray));
    *err = dynamic_array_init(arr, GetIntFieldInfo());
    if (*err == ERR_ALLOCATION_FAIL) {
        return NULL;
    }

    const char* p = str;
    char* end;

    while (*p) {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        errno = 0;
        long val = strtol(p, &end, 10);

        if (p == end) {
            *err = ERR_NON_NUMERIC_INPUT;
            dynamic_array_free(arr);
            free(arr);
            return NULL;
        }
        if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            *err = ERR_NUM_OVERFLOW;
            dynamic_array_free(arr);
            free(arr);
            return NULL;
        }

        int int_val = (int)val;
        dynamic_array_add(arr, &int_val);
        p = end;
    }
    return arr;
}

DynamicArray* string_to_values_double(const char* str, ErrorCode *err) {
    DynamicArray* arr = malloc(sizeof(DynamicArray));
    *err = dynamic_array_init(arr, GetDoubleFieldInfo());
    if (*err == ERR_ALLOCATION_FAIL) {
        return NULL;
    }

    const char* p = str;
    char* end;

    while (*p) {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        errno = 0;
        double val = strtod(p, &end);

        if (p == end) {
            *err = ERR_NON_NUMERIC_INPUT;
            dynamic_array_free(arr);
            free(arr);
            return NULL;
        }
        if (errno == ERANGE) {
            *err = ERR_NUM_OVERFLOW;
            dynamic_array_free(arr);
            free(arr);
            return NULL;
        }

        dynamic_array_add(arr, &val);
        p = end;
    }
    return arr;
}

DynamicArray* string_to_values_int_with_count(const char* str, size_t count, ErrorCode *err) {
    DynamicArray* arr = string_to_values_int(str, err);
    if (!arr) return NULL;

    if (arr->size != count) {
        *err = ERR_UNEXPECTED_INPUT_COUNT;
        dynamic_array_free(arr);
        free(arr);
        return NULL;
    }
    return arr;
}

DynamicArray* ReadManyInt(ErrorCode *err) {
    char *line = my_getline(1024);
    
    DynamicArray* arr = string_to_values_int(line, err);
    free(line);
    return arr;
}

DynamicArray* ReadManyDouble(ErrorCode *err) {
    char *line = my_getline(1024);

    DynamicArray* arr = string_to_values_double(line, err);
    free(line);
    return arr;
}

DynamicArray* ReadManyIntWithCount(size_t count, ErrorCode *err) {
    char *line = my_getline(1024);

    DynamicArray* arr = string_to_values_int_with_count(line, count, err);
    free(line);
    return arr;
}

int ReadOneInt(ErrorCode *err) {
    DynamicArray* arr = ReadManyIntWithCount(1, err);
    if (!arr) return 0;

    int val = ((int*)arr->data)[0];
    dynamic_array_free(arr);
    free(arr);
    return val;
}
