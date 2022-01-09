cmake_minimum_required( VERSION 3.0 )

project( "test" )

add_subdirectory( "lib/ArbitaryIntegerLibrary" )

add_executable( test test.cpp )

target_include_directories( test PUBLIC lib/ArbitaryIntegerLibrary/include )

target_link_libraries( test arbitary_integer_library )
