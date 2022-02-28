#include "ArbitaryIntegerLibrary/integer.hpp"

#include <limits>

#include <iostream>

int main()
{
    Arbitary::Integer integer(std::numeric_limits<unsigned>::max());

    integer.dump();

    integer++;

    integer.dump();

    integer--;

    integer.dump();

    integer = Arbitary::Integer();

    integer.dump();

    integer--;

    integer.dump();

    integer--;

    integer.dump();

    integer++;

    integer.dump();

    integer++;

    integer.dump();

    integer++;

    integer.dump();

    integer--;

    integer.dump();
}