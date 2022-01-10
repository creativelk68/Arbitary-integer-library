#include "ArbitaryIntegerLibrary/integer.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


// Define bool

#define bool  int
#define true  1
#define false 0


struct Integer_struct construct_integer()
{
    /*
    *   Constructs a zero-initialized Integer_struct and returns it.
    */
    struct Integer_struct integer;
    integer.digits = (unsigned*) malloc(sizeof(unsigned));
    *integer.digits = 0u;
    integer.size = 1u;

    integer.is_negative = false;

    return integer;
}


struct Integer_struct construct_integer_from_int32(const int32_t value)
{
    /*
    *   Constructs an Integer_struct, initializes it, and returns it.
    *
    *   Parameters:
    *   - int32_t value : Decimal value, the integer will have after being contructed
    * 
    *   Returns: The constructed integer with the same value as the parameter. The integer must be freed using destruct_integer(struct Integer_struct*)
    *            to prevent memory leaks.
    */ 
    struct Integer_struct integer;

    if (sizeof(unsigned) > 4) { integer.digits = (unsigned*) malloc(sizeof(unsigned)); }
    else                      { integer.digits = (unsigned*) malloc(4u); }

    integer.is_negative = value >> 31;
    *integer.digits = (integer.is_negative) ? ~abs(value) : abs(value);

    integer.size = 1u;

    return integer;
}


struct Integer_struct construct_integer_from_uint32(const uint32_t value)
{
    /*
    *   Constructs an Integer_struct, initializes it, and returns it.
    *
    *   Parameters:
    *   - uint32_t value : Decimal value, the integer will have after being contructed
    * 
    *   Returns: The constructed integer with the same value as the parameter. The integer must be freed using destruct_integer(struct Integer_struct*)
    *            to prevent memory leaks
    */ 
    struct Integer_struct integer;
    integer.digits = (unsigned*) malloc(4u);

    integer.is_negative = false;
    *integer.digits = value;

    integer.size = 1u;

    return integer;
}

void destruct_integer(struct Integer_struct* integer) {
    /*
    *   Frees all dynamic allocated ressources of the integer.
    *
    *   Parameters:
    *   - struct Integer_struct* integer : A pointer to an instance of the Integer_struct struct, whose ressources are supposed to be freed after this function call
    * 
    *   Returns: nothing, just void
    */ 
    free((void*) integer->digits);
    integer->digits = NULL;
}


void dump_integer(const struct Integer_struct* integer)
{
    if (integer->is_negative)
    {
        putchar('-');

        for (unsigned i = 0u; i < integer->size; i++) { printf("%u ", ~integer->digits[i]); }
    } else
    {
        for (unsigned i = 0u; i < integer->size; i++) { printf("%u ", integer->digits[i]); }
    }
}