cmake_minimum_required( VERSION 3.0 )

project( "Arbitary Integer Library" )

set(
    SRCS
    "src/integer.c"
    "src/integer.cpp"
)

add_library( arbitary_integer_library STATIC ${SRCS} )