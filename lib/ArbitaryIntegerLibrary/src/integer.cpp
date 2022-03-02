#include "ArbitaryIntegerLibrary/integer_impl.hpp"
#include "ArbitaryIntegerLibrary/integer.hpp"

#include <limits>
#include <stdexcept>
#include <cstring>
#include <vector>

#include <algorithm>

#include <iostream>

static_assert(sizeof(unsigned) == 2u || sizeof(unsigned) == 4u || sizeof(unsigned) == 8u, "Unexpected size of datatype \"unsigned\" (expected either 2, 4 or 8 bytes)");

#define ABS(x) ((x) < 0) ? -(x) : (x)


// Printing

std::ostream& Arbitary::operator<<(std::ostream& os, const Arbitary::Integer& integer)
{
    if (integer.get_is_negative()) { os << '-'; } 

    os << integer.get_first_digit();

    for (unsigned i = 0; i < integer.get_size(); i++) { os << integer.get_allocated_digit(i) << ' '; }

    return os;
}

void Arbitary::dump_integer(const Integer_struct& integer)
{
    if (integer.is_negative) { putchar('-'); }

    std::cout << integer.first_digit << ' ';

    for (unsigned i = 0u; i < integer.extra_digits.size(); i++) { printf("%u ", integer.extra_digits[i]); }

    putchar('\n');
}


// Constructors

Arbitary::Integer_struct Arbitary::construct_integer()
{
    /*
    *   Constructs a zero-initialized Integer_struct and returns it.
    */
    Integer_struct integer;

    integer.is_negative = false;

    integer.first_digit = 0u;

    return integer;
}

Arbitary::Integer_struct Arbitary::construct_integer_from_int32(const int32_t& value)
{
    /*
    *   Constructs an Integer_struct, initializes it, and returns it.
    *
    *   Parameters:
    *   - int32_t value : Decimal value the integer will have after being contructed
    * 
    *   Returns: The constructed integer with the same value as the parameter.
    */

    Integer_struct integer;

    integer.is_negative = value < 0;

    if constexpr(sizeof(unsigned) == 4u || sizeof(unsigned) == 8u) { integer.first_digit = static_cast<unsigned>(ABS(value)); }
    else
    {
        constexpr uint32_t base16 = 65536;

        const uint32_t abs_val = ABS(value);

        if (abs_val < base16)
        {
            integer.first_digit = static_cast<unsigned>(abs_val);
        } else
        {
            integer.extra_digits.push_back(abs_val % base16);
            integer.first_digit = abs_val / base16;
        }
    }    

    return integer;
}

Arbitary::Integer_struct Arbitary::construct_integer_from_uint32(const uint32_t& value)
{
    /*
    *   Constructs an Integer_struct, initializes it, and returns it.
    *
    *   Parameters:
    *   - uint32_t value : Decimal value the integer will have after being contructed
    * 
    *   Returns: The constructed integer with the same value as the parameter.
    */ 
    Integer_struct integer;

    integer.is_negative = false;

    if constexpr (sizeof(unsigned) == 4u || sizeof(unsigned) == 8u) { integer.first_digit = static_cast<unsigned>(value); }
    else
    {
        constexpr uint32_t base16 = 65536;

        if (value >= base16)
        {
            integer.extra_digits.push_back(value % base16);
            integer.first_digit = value / base16;
        } else
        {
            integer.first_digit = static_cast<unsigned>(value);
        }
    }

    return integer;
}


Arbitary::Integer_struct Arbitary::construct_integer_from_int64(const int64_t& value)
{
    /*
    *   Constructs an Integer_struct, initializes it, and returns it.
    *
    *   Parameters:
    *   - int64_t value : Decimal value the integer will have after being contructed
    * 
    *   Returns: The constructed integer with the same value as the parameter.
    */
    
    Integer_struct integer;

    integer.is_negative = value < 0;

    if constexpr (sizeof(unsigned) == 8u) { integer.first_digit = static_cast<unsigned>( ABS(value) ); }
    else if constexpr (sizeof(unsigned) == 4u)
    {
        constexpr uint64_t base32 = 4294967296;

        const uint64_t abs_val = ABS(value);

        if (abs_val < base32)
        {
            integer.first_digit = static_cast<unsigned>(abs_val);            
        } else
        {
            integer.extra_digits.push_back(abs_val % base32);
            integer.first_digit = abs_val / base32;
        }

    } else
    {
        constexpr uint32_t base16 = 65536;

        const uint64_t abs_val = ABS(value);

        if (abs_val < base16)
        {
            integer.first_digit = static_cast<unsigned>(value);
        } else
        {
            uint64_t rem = abs_val;

            while (rem >= base16)
            {
                integer.extra_digits.push_back(rem % base16);
                rem /= base16;
            }

            std::reverse(integer.extra_digits.begin(), integer.extra_digits.end());

            integer.first_digit = rem;
        }
    }

    return integer;
}


Arbitary::Integer_struct Arbitary::construct_integer_from_uint64(const uint64_t& value)
{
    /*
    *   Constructs an Integer_struct, initializes it, and returns it.
    *
    *   Parameters:
    *   - uint64_t value : Decimal value the integer will have after being contructed
    * 
    *   Returns: The constructed integer with the same value as the parameter.
    */

    Integer_struct integer;

    integer.is_negative = false;

    if constexpr (sizeof(unsigned) == 8u) { integer.first_digit = static_cast<unsigned>(value); }
    else if constexpr (sizeof(unsigned) == 4u)
    {
        constexpr uint64_t base32 = 4294967296;

        if (value < base32) { integer.first_digit = static_cast<unsigned>(value); }
        else
        {
            integer.extra_digits.push_back(value % base32);
            integer.first_digit = value / base32;
        }
    } else
    {
        constexpr int32_t base16 = 65536;

        if (value < base16) { integer.first_digit = static_cast<unsigned>(value); }
        else
        {
            uint64_t rem = value;

            while (rem >= base16)
            {
                integer.extra_digits.push_back(rem % base16);
                rem /= base16;
            }

            std::reverse(integer.extra_digits.begin(), integer.extra_digits.end());

            integer.first_digit = static_cast<unsigned>(rem);
        }
    }

    return integer;
}


// Modifying method implementations

// Increment an Integer_struct instance
void Arbitary::increment_integer(Integer_struct& integer)
{
    /*
    *   Increments the Integer-instance by 1
    *
    *   Parameters:
    *   - struct Integer_struct& integer : A reference to an instance of the Integer_struct struct, whose value should be incremented
    * 
    *   Returns: void
    */ 

   if (integer.extra_digits.empty())
   {

        // Increment and check for overflow
        if (integer.is_negative)
        {
            if (--integer.first_digit == 0u)
            {
                integer.is_negative = false;
                return;
            }
        }
        else 
        {
            if (++integer.first_digit != 0u) { return; }

            // Handle overflow
            integer.extra_digits.push_back(0u);
            integer.first_digit = 1u;      
            return;
        }
   }

    bool carry = false;

    const size_t size = integer.extra_digits.size();

    for (unsigned i = size - 1; i < size; i--)
    {
        integer.extra_digits[i]++;
        if (integer.extra_digits[i] == 0u) { carry = true; continue; }
        return;
    }

    if (carry)
    {
        if (++integer.first_digit != 0u) { return; }

        // Handle overflow
        integer.first_digit++;
        integer.extra_digits.push_back(0u);
    }
}


// Decrement an Integer_struct instance
void Arbitary::decrement_integer(Integer_struct& integer)
{
    /*
    *   Decrements the Integer-instance by 1
    *
    *   Parameters:
    *   - struct Integer_struct& integer : A reference to an instance of the Integer_struct struct, whose value should be decremented
    * 
    *   Returns: void
    */

    if (integer.extra_digits.empty())
    {
        if (integer.first_digit == 0u)
        {
            integer.is_negative = true;
            integer.first_digit = 1u;
            return;
        }
        
        if (integer.first_digit == std::numeric_limits<unsigned>::max() && integer.is_negative)
        {
            integer.first_digit = 1u;
            integer.extra_digits.push_back(0u);
            return;
        }

        if (integer.is_negative) { integer.first_digit++; }
        else                     { integer.first_digit--; }

        return;
    }

    bool carry = false;

    const size_t size = integer.extra_digits.size();

    if (integer.is_negative)
    {
        for (unsigned i = size - 1; i < size; i--)
        {
            if (++integer.extra_digits[i] == 0u) { carry = true; }
        }
    }
    else
    {
        for (unsigned i = size - 1; i < size; i--)
        {
            if (integer.extra_digits[i]-- == 0u) { carry = true; }
        }
    }

    if (carry)
    {
        if (integer.is_negative && integer.first_digit == std::numeric_limits<unsigned>::max())
        {
            integer.first_digit = 1u;
            integer.extra_digits.push_back(0u);
        }
        else
        {
            integer.first_digit = integer.extra_digits[0];

            if (size == 1u) { integer.extra_digits.pop_back(); return; }

            std::rotate(integer.extra_digits.begin(), integer.extra_digits.begin() + 1, integer.extra_digits.end());
            integer.extra_digits.pop_back();
        }
    }
}
