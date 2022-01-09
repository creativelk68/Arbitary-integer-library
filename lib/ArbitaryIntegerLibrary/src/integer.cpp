#include "ArbitaryIntegerLibrary/integer.hpp"

#include <iostream>


void Arbitary::Integer::dump() const {
    if (m_integer.is_negative)
    { 
        std::cout << '-';

        for (unsigned i = 0; i < m_integer.size; i++) { std::cout << ~m_integer.digits[i] << ' '; }

    } else { for (unsigned i = 0; i < m_integer.size; i++) { std::cout << m_integer.digits[i] << ' '; } }

    std::cout << std::endl;
}

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