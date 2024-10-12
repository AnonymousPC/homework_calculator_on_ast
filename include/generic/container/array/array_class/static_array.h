#pragma once

// Base

namespace aux
{
    template < class type, int len > struct static_array_base;
}


/// Class static_array

template < class type, int len >
class static_array
    extends public aux::static_array_base<type,len>,       // Allows aggregtate initializations.
            public array_algo<static_array<type,len>,type> // Does not needs a position in aggregrate.
{
    private: // Precondition
        static_assert ( not std::is_const<type>::value and not std::is_volatile<type>::value and not std::is_reference<type>::value );
        static_assert ( len >= 0 );

    public: // Typedef
        using  value_type     = type;
        using  iterate_type   = type;
        using  iterator       = type*;
        using  const_iterator = const type*;
        using  array_algo     = array_algo<static_array,type>;
        struct array_tag { };

    public: // Interface
        constexpr static int            size        ( );
        constexpr static bool           empty       ( );
        constexpr        iterator       begin       ( );
        constexpr        const_iterator begin       ( )     const;
        constexpr        iterator       end         ( );
        constexpr        const_iterator end         ( )     const;
        constexpr        type&          operator [] ( int );
        constexpr const  type&          operator [] ( int ) const;

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;
};

#include "static_array.cpp"
