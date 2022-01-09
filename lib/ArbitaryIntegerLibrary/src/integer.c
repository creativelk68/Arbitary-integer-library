#include "ArbitaryIntegerLibrary/integer.h"

#include <stdlib.h>
#include <stdint.h>


struct Integer_struct construct_integer()
{
    struct Integer_struct integer;
    integer.digits = (unsigned*) malloc(1u * sizeof(unsigned));
    *integer.digits = 0u;
    integer.size = 1u;

    integer.is_negative = false;

    return integer;
}


struct Integer_struct construct_integer_from_int32(const int32_t value)
{
    struct Integer_struct integer;
    integer.digits = (unsigned*) malloc(4u);

    integer.is_negative = value >> 31;
    *integer.digits = (integer.is_negative) ? ~abs(value) : abs(value);

    integer.size = 1u;

    return integer;
}


struct Integer_struct construct_integer_from_uint32(const uint32_t value)
{
    struct Integer_struct integer;
    integer.digits = (unsigned*) malloc(4u);

    integer.is_negative = false;
    *integer.digits = value;

    integer.size = 1u;

    return integer;
}

void destruct_integer(struct Integer_struct* integer)
{
    free((void*) integer->digits);
}