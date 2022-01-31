#include "ArbitaryIntegerLibrary/integer.hpp"

#include <limits>

#include <iostream>

int main()
{
    Arbitary::Integer integer(std::numeric_limits<unsigned>::max());

    std::cout << integer << std::endl;

    integer.inc();

    std::cout << integer << std::endl;
}