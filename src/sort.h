#ifndef SORT_H
#define SORT_H

#include "field_info.h"
#include "dynamic_array.h"

ErrorCode swap(void *a, void *b, FieldInfo *field_info);
ErrorCode quicksort(DynamicArray *arr, int low, int high);

#endif