#include <iostream>
#include "BitBuilder.hpp"


using namespace BitBuilder;

int main( int argc, char **argv )
{
    std::cout << argc << argv[0] << std::endl;

    std::cout << "runtime test" << std::endl;
    std::cout << std::hex;
    std::cout << uint32_t(Word<4>(4).bit<0>()) << " "
              << uint32_t(Word<4>(4).bit<1>()) << " "
              << uint32_t(Word<4>(4).bit<2>()) << " " 
              << uint32_t(Word<4>(4).bit<3>()) << std::endl;

    std::cout << uint32_t(uint8_t(flag( true ) | flag( true ) | flag( true ))) << std::endl;

    std::cout << uint32_t( Word<4>( 0xD ) | Word<4>( 0xA ) | Word<4>( 0xE ) | Word<4>( 0xD ))
              << std::endl;

    std::cout << uint32_t(Word<16>( 0xDEAD ).evenParityBit()) << std::endl;
    std::cout << uint32_t(Word<16>( 0xDEAC ).evenParityBit()) << std::endl;
    return 0;
}

