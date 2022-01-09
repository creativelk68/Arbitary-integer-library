#pragma once

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

// Define bool

#define bool  int
#define true  1
#define false 0

#ifdef __cplusplus
extern "C" {
#endif

struct Integer_struct
{
    bool is_negative;
    unsigned* digits;
    size_t size;
};


struct Integer_struct construct_integer();

struct Integer_struct construct_integer_from_int32(const int32_t value);

struct Integer_struct construct_integer_from_uint32(const uint32_t value);


void destruct_integer(struct Integer_struct* integer);

#ifdef __cplusplus
}
#endif

#undef bool