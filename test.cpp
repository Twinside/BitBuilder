#include <iostream>
#include "BitBuilder.hpp"


using namespace BitBuilder;

int main( int argc, char **argv )
{
    std::cout << argc << argv[0] << std::endl;


    typedef detail::IntegralType<3>::type t3;
    typedef detail::IntegralType<5>::type t5;
    typedef detail::IntegralType<14>::type t14;
    typedef detail::IntegralType<16>::type t16;
    typedef detail::IntegralType<24>::type t24;
    typedef detail::IntegralType<32>::type t32;
    typedef detail::IntegralType<40>::type t40;
    typedef detail::IntegralType<63>::type t63;
    typedef detail::IntegralType<64>::type t64;

    std::cout << sizeof(t3) << " 3 " << typeid(t3).name() << std::endl;
    std::cout << sizeof(t5) << " 5 " << typeid(t5).name() << std::endl;
    std::cout << sizeof(t14) << " 14 " << typeid(t14).name() << std::endl;
    std::cout << sizeof(t16) << " 16 " << typeid(t16).name() << std::endl;
    std::cout << sizeof(t24) << " 24 " << typeid(t24).name() << std::endl;
    std::cout << sizeof(t32) << " 32 " << typeid(t32).name() << std::endl;
    std::cout << sizeof(t40) << " 40 " << typeid(t40).name() << std::endl;
    std::cout << sizeof(t63) << " 63 " << typeid(t63).name() << std::endl;
    std::cout << sizeof(t64) << " 64 " << typeid(t64).name() << std::endl;

    std::cout << "runtime test" << std::endl;
    std::cout << std::hex;
    std::cout << uint32_t(Word<4>(4).bit<0>()) << " "
              << uint32_t(Word<4>(4).bit<1>()) << " "
              << uint32_t(Word<4>(4).bit<2>()) << " " 
              << uint32_t(Word<4>(4).bit<3>()) << std::endl;

    std::cout << uint32_t(uint8_t(flag( true ) | flag( true ) | flag( true ))) << std::endl;

    std::cout << uint32_t( Word<4>( 0xD ) | Word<4>( 0xA ) | Word<4>( 0xE ) | Word<4>( 0xD ))
              << std::endl;
    return 0;
}

