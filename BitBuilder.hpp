#ifndef __BITBUILDER_HPP__
#define __BITBUILDER_HPP__

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/sizeof.hpp>

#include <stdint.h>

namespace BitBuilder
{
    namespace detail
    {
        using namespace boost;
        using namespace boost::mpl;
        

        /** Find the smallest possible integral type which can carry
         * bitCount bits.
         */
        template <uint32_t bitCount>
        class IntegralType
        {
            typedef typename
                    list<uint8_t, uint16_t, uint32_t, uint64_t>::type typeList;
            typedef // typename 
                    greater_equal< times< sizeof_< _1 >, integral_c<std::size_t, 8u> >
                                 , integral_c<std::size_t, bitCount> > searchPredicate;

            typedef typename find_if< typeList, searchPredicate >::type searchResult;

        public:
            typedef typename deref<searchResult>::type type;
        };
    }

    /**
     *
     */
    template <int bitCount>
    class Word
    {
    public:
        typedef typename detail::IntegralType<bitCount>::type inner_type;

        explicit Word( inner_type t ) : data( t )
        {}

        template <int toAppend>
        Word<bitCount + toAppend> operator |( Word<toAppend> p ) const
            { return append(p); }

        template <int toAppend>
        Word<bitCount + toAppend>   append( Word<toAppend> p ) const
        {
            typedef Word<bitCount + toAppend> ret_type;
            typedef typename ret_type::inner_type  upCast;
            typedef typename Word<toAppend>::inner_type otherType;

            return ret_type( static_cast<upCast>(data)
                           | (static_cast<upCast>(static_cast<otherType>(p)) << bitCount) );
        }

        Word<bitCount + 1>  appendNotPreviousBit() const
        {
            typedef Word<bitCount + 1>      ret_type;
            typedef typename ret_type::inner_type    upCast;

            return Word<bitCount + 1>((static_cast<upCast>( data ) & 
                                       (static_cast<upCast>(1) << (bitCount - 1))) >> (bitCount - 1));
        }

        template <int bitPosition>
        Word<1> bit() const
        {
            return Word<1>( (data & (1 << bitPosition)) >> bitPosition );
        }

        Word<1> bit(size_t  bitPosition)
        {
            return Word<1>( (data & (1 << bitPosition)) >> bitPosition );
        }

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

