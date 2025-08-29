#ifndef MANUAL_READ_H
#define MANUAL_READ_H

#include <stddef.h>

#include "dynamic_array.h"

char *my_getline(size_t size);

DynamicArray* string_to_values_int(const char* str, ErrorCode *err);
DynamicArray* string_to_values_double(const char* str, ErrorCode *err);
DynamicArray* string_to_values_int_with_count(const char* str, size_t count, ErrorCode *err);

DynamicArray* ReadManyInt(ErrorCode *err);
DynamicArray* ReadManyDouble(ErrorCode *err);
DynamicArray* ReadManyIntWithCount(size_t count, ErrorCode *err);
int ReadOneInt(ErrorCode *err);

#endif