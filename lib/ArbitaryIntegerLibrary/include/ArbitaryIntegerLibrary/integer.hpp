#pragma once

#include "integer.h"

#include <ostream>

namespace Arbitary
{
    class Integer
    {
        // Actual Integer which is handled by all methods. This class is just a C++-wrapper for the Integer_struct struct
        // All digits inside this class are, except if not extra specified, not in base 10 but in base 2^32 number system

        Integer_struct m_integer;

    public:
        // Constructors and destructor


        // Default constructor. Zero-initializes the integer
        inline Integer() : m_integer(construct_integer()) {}


        // Initializes the integer with a regular, decimal signed 32-bit value
        explicit inline Integer(const int32_t& value) : m_integer(construct_integer_from_int32(value)) {}

        // Initializes the integer with a regular, decimal unsigned 32-bit value
        explicit inline Integer(const uint32_t& value) : m_integer(construct_integer_from_uint32(value)) {}

        // Destructs the integer
        inline ~Integer() { destruct_integer(&m_integer); }


        
        // Getters and methods for getting information about the integer-instance

        // Dumps the sign, if negative, and each digit separated by space into the console
        inline void dump() const { dump_integer(&m_integer); }

        // Returns, whether the instance is negative
        inline bool get_is_negative() const { return m_integer.is_negative; }

        // Returns the amount of digits
        inline size_t get_size() const { return m_integer.size; }

        // Returns a read-only pointer to the digits
        inline const unsigned* get_digits() const { return m_integer.digits; }

        // Returns a specific digit at the given index
        inline unsigned get_digit(const size_t& index) const { return m_integer.digits[index]; }



        // Modifing methods

        // Returns a regular pointer to the digits
        inline unsigned* get_digits() { return m_integer.digits; }
    };


    // Function for printing the value of an Integer into the terminal using std::cout

    std::ostream& operator<<(std::ostream& os, const Arbitary::Integer& integer);

} // namespace Integer
