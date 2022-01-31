#pragma once

#include <cstdlib>
#include <cstdint>
#include <limits>


// This struct is the real Integer while the class is just a wrapper of it

    namespace Arbitary
    {

    struct Integer_struct
    {
        bool is_negative;
        unsigned* digits; // Digits are with two's-complement
        size_t size, capacity;
    };


    // This function returns a new zero-initialized integer. Integer must be freed using destruct_integer(Integer_struct*) function or manually by freeing each digit.

    Integer_struct construct_integer();


    // This function does the same as the contruct_integer() function, but initializes the Integers value with the parameter.

    Integer_struct construct_integer_from_int32(const int32_t& value);


    // Same as construct_integer_from_int32(const int32_t) but the parameter is unsigned.

    Integer_struct construct_integer_from_uint32(const uint32_t& value);


    // Increment an Integer_struct instance
    void increment_integer(Integer_struct& integer);

    // Decrement an Integer_struct instance
    // void decrement(Integer_struct& integer); // Not implemented yet


    // Invalidates the Integer instance by freeing the digits array and setting it to a nullptr. 

    void destruct_integer(Integer_struct& integer);


    void dump_integer(const Integer_struct& integer);
}