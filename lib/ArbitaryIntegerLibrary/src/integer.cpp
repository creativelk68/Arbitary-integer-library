#include "ArbitaryIntegerLibrary/integer_impl.hpp"
#include "ArbitaryIntegerLibrary/integer.hpp"

#include <limits>
#include <stdexcept>

#include <iostream>

// Printing

std::ostream& Arbitary::operator<<(std::ostream& os, const Arbitary::Integer& integer)
{
    if (integer.get_is_negative())
    {
        os << '-';

        for (unsigned i = 0; i < integer.get_size(); i++) { os << ~integer.get_digit(i) << ' '; }
    } else
    {
        for (unsigned i = 0; i < integer.get_size(); i++) { os << integer.get_digit(i) << ' '; }
    }
     return os;
}

void Arbitary::dump_integer(const Integer_struct& integer)
{
    if (integer.is_negative)
    {
        putchar('-');

        for (unsigned i = 0u; i < integer.size; i++) { printf("%u ", ~integer.digits[i]); }
    } else
    {
        for (unsigned i = 0u; i < integer.size; i++) { printf("%u ", integer.digits[i]); }
    }
}


// Constructors

Arbitary::Integer_struct Arbitary::construct_integer()
{
    /*
    *   Constructs a zero-initialized Integer_struct and returns it.
    */
    Integer_struct integer;
    integer.digits = (unsigned*) malloc(sizeof(unsigned));
    *integer.digits = 0u;
    integer.capacity = integer.size = 1u;

    integer.is_negative = false;

    return integer;
}

Arbitary::Integer_struct Arbitary::construct_integer_from_int32(const int32_t& value)
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
    Integer_struct integer;

    integer.digits = reinterpret_cast<unsigned*>(malloc(sizeof(unsigned)));

    integer.is_negative = static_cast<bool>(value >> 31);
    *integer.digits = (integer.is_negative) ? ~abs(value) : abs(value);

    integer.size = integer.capacity = 1u;

    return integer;
}

Arbitary::Integer_struct Arbitary::construct_integer_from_uint32(const uint32_t& value)
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
    Integer_struct integer;
    integer.digits = reinterpret_cast<unsigned*>(malloc(4u));

    integer.is_negative = false;
    *integer.digits = value;

    integer.size = integer.capacity = 1u;

    return integer;
}


// Modifying method implementations

// Increment an Integer_struct instance
void Arbitary::increment_integer(Integer_struct& integer)
{
    // Check for Integer validity
    if (integer.digits == nullptr) throw std::invalid_argument("integer is invalid!");

    bool carry = false;

    for (unsigned i = integer.size - 1; i < integer.size; i--)
    {
        integer.digits[i]++;
        if (integer.digits[i] == 0u) { carry = true; }
    }

    if (carry)
    {
        if (integer.size < integer.capacity) { integer.digits[integer.size++] = 1u; return; }

        integer.digits = reinterpret_cast<unsigned*>( realloc(integer.digits, (integer.capacity + 1u) * sizeof(unsigned)) );
        if (integer.digits == nullptr) throw std::bad_alloc();

        integer.capacity++;
        integer.size++;

        integer.digits[0] = 1u;
        integer.digits[integer.size-1] = 0u;
    }
}

// Destructor

void Arbitary::destruct_integer(Integer_struct& integer) {
    /*
    *   Frees all dynamic allocated ressources of the integer.
    *
    *   Parameters:
    *   - struct Integer_struct* integer : A pointer to an instance of the Integer_struct struct, whose ressources are supposed to be freed after this function call
    * 
    *   Returns: nothing, just void
    */ 
    free((void*) integer.digits);
    integer.digits = nullptr;
}
