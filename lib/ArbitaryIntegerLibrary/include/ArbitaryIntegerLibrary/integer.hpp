#pragma once

#include "integer_impl.hpp"

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

        // Initializes the integer with a decimal signed 32-bit value
        explicit inline Integer(const int32_t& value) : m_integer(construct_integer_from_int32(value)) {}

        // Initializes the integer with a decimal unsigned 32-bit value
        explicit inline Integer(const uint32_t& value) : m_integer(construct_integer_from_uint32(value)) {}

        // Initializes the integer with a decimal signed 64-bit value
        explicit inline Integer(const int64_t& value) : m_integer(construct_integer_from_int64(value)) {}

        // Initializes the integer with a decimal unsigned 64-bit value
        explicit inline Integer(const uint64_t& value) : m_integer(construct_integer_from_uint64(value)) {}
        
        
        // Getters and methods for getting information about the integer-instance

        // Dumps the sign, if negative, and each digit separated by space into the console
        inline void dump() const { dump_integer(m_integer); }

        // Returns, whether the instance is negative
        inline bool get_is_negative() const { return m_integer.is_negative; }

        // Returns the amount of extra allocated digits
        inline size_t get_size() const { return m_integer.extra_digits.size(); }

        // Returns a const ref to the std::vector of the allocated digits
        inline const std::vector<unsigned>& get_allocated_digits() const { return m_integer.extra_digits; }

        // Returns a specific allocated digit at the given index
        inline unsigned get_allocated_digit(const size_t& index) const { return m_integer.extra_digits[index]; }

        // Returns the non-allocated digit
        inline const unsigned& get_first_digit() const { return m_integer.first_digit; }



        // Modifing methods

        // Increment
        inline void inc() { increment_integer(m_integer); }

        // Decrement
        inline void dec() { decrement_integer(m_integer); }

        // Returns a non-const reference to the non-allocated digit
        inline unsigned& get_first_digit() { return m_integer.first_digit; }

        // Returns a ref to the std::vector of the allocated digits
        inline std::vector<unsigned>& get_allocated_digits() { return m_integer.extra_digits; }

    
        // Operators

        // Increment operators
        inline Integer& operator++()    { inc(); return *this; }  // Prefix
        inline Integer& operator++(int) { inc(); return *this; }  // Postfix

        // Decrement operators
        inline Integer& operator--()    { dec(); return *this; }  // Prefix
        inline Integer& operator--(int) { dec(); return *this; }  // Postfix
    };


    // Function for printing the value of an Integer into the terminal using std::cout

    std::ostream& operator<<(std::ostream& os, const Arbitary::Integer& integer);

} // namespace Integer
