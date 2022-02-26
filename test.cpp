#include "ArbitaryIntegerLibrary/integer.hpp"

#include <limits>

#include <iostream>

int main()
{
    Arbitary::Integer integer(std::numeric_limits<unsigned>::max());

    std::cout << integer << std::endl;

    integer.inc();

    std::cout << integer << std::endl;

    integer.dec();

    std::cout << integer << std::endl;

    Arbitary::Integer integer2(0);

    std::cout << integer2 << std::endl;
    
    integer2--;

    std::cout << integer2 << std::endl;

}