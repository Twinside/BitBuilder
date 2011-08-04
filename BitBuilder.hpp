#ifndef __BITBUILDER_HPP__
#define __BITBUILDER_HPP__

#include <boost/integer.hpp>

#include <stdint.h>

namespace BitBuilder
{
    /** Wrapper around an integral type for storing bits.
     * Provide some high-level facility to write declaratively
     * the content of the integer at the byte level. Support
     * slicing.
     */
    template <int bitCount>
    class Word
    {
    public:
        typedef typename boost::uint_t<bitCount>::least inner_type;

        explicit Word( inner_type t ) : data( t )
        {}

        /** Bit concatenation operator.
         * Place the right hand side of the operator into the Most significant
         * bits for the word. Operator version of the append method.
         *
         * example:
         * (Word<4>(0xD) | Word<4>(0xA) | Word<4>(0xE) | Word<4>(0xD)) == 0xDEAD
         * \see append
         */
        template <int toAppend>
        Word<bitCount + toAppend> operator |( Word<toAppend> p ) const
            { return append(p); }

        /** Bit concatenation method.
         * Place the argument into the Most significant
         * bits for the word. Operator version of the append method.
         *
         * example:
         * (Word<4>(0xD).append(Word<4>(0xA))
         *              .append(Word<4>(0xE))
         *              .append(Word<4>(0xD))) == 0xDEAD
         */
        template <int toAppend>
        Word<bitCount + toAppend>   append( Word<toAppend> p ) const
        {
            typedef Word<bitCount + toAppend> ret_type;
            typedef typename ret_type::inner_type  upCast;
            typedef typename Word<toAppend>::inner_type otherType;

            return ret_type( static_cast<upCast>(data)
                           | (static_cast<upCast>(static_cast<otherType>(p)) << bitCount) );
        }

        /** Given the last written bit at bitCount - 1 position, append
         * it's opposite in the word.
         *
         * Examples:
         * Word<4>(7).appendNotPreviousBit() == 0x17
         * Word<4>(8).appendNotPreviousBit() == 0x08
         */
        Word<bitCount + 1>  appendNotPreviousBit() const
        {
            typedef Word<bitCount + 1>      ret_type;
            typedef typename ret_type::inner_type    upCast;

            return Word<bitCount + 1>((static_cast<upCast>( data ) & 
                                       (static_cast<upCast>(1) << (bitCount - 1))) >> (bitCount - 1));
        }

        /** Return the bit at bitPosition, starting at 0 for the
         * least significant bit.
         *
         * example:
         * Word<4>(4).bit<2>() == 1
         * Word<4>(4).bit<1>() == 0
         */
        template <int bitPosition>
        Word<1> bit() const
        {
            inner_type one = static_cast<inner_type>(1);
            return Word<1>( (data & (one << bitPosition)) >> bitPosition );
        }

        /** Return the bit at bitPosition, starting at 0 for the
         * least significant bit.
         *
         * example:
         * Word<4>(4).bit(2) == 1
         * Word<4>(4).bit(1) == 0
         */
        Word<1> bit(size_t  bitPosition) const
        {
            inner_type one = static_cast<inner_type>(1);
            return Word<1>( (data & (one << bitPosition)) >> bitPosition );
        }


        /** Get back the built data */
        operator inner_type() const { return data; }

    private:
        inner_type data;
    };


    /** Helper function to help write a single bit. */
    Word<1> flag( bool yesno )
    {
        typedef Word<1>::inner_type castType;
        return Word<1>( static_cast<castType>(yesno) );
    }
}

#endif /* __BITBUILDER_HPP__ */

