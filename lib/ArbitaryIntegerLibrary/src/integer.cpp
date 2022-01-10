#include "ArbitaryIntegerLibrary/integer.hpp"

#include <iostream>

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