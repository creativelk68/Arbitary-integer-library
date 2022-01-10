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


// This struct is the real Integer while the class is just a wrapper of it

struct Integer_struct
{
    bool is_negative;
    unsigned* digits; // Digits are with two's-complement
    size_t size;
};


// This function returns a new zero-initialized integer. Integer must be freed using destruct_integer(Integer_struct*) function or manually by freeing each digit.

struct Integer_struct construct_integer();


// This function does the same as the contruct_integer() function, but initializes the Integers value with the parameter.

struct Integer_struct construct_integer_from_int32(const int32_t value);


// Same as construct_integer_from_int32(const int32_t) but the parameter is unsigned.

struct Integer_struct construct_integer_from_uint32(const uint32_t value);


// Invalidates the Integer instance by freeing the digits array and setting it to a nullptr. 

void destruct_integer(struct Integer_struct* integer);


void dump_integer(const struct Integer_struct* integer);

#ifdef __cplusplus
}
#endif

#undef bool