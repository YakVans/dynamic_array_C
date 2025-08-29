#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>

#include "errors.h"

typedef struct FieldInfo{
    size_t element_size;
    ErrorCode (*copy)(void *dest, const void *src);
    ErrorCode (*free)(void *element);
    IntErrorPair (*compare)(const void *a, const void *b);
    ErrorCode (*print)(const void *element);
} FieldInfo;

FieldInfo *GetIntFieldInfo(void);
FieldInfo *GetDoubleFieldInfo(void);

#endif