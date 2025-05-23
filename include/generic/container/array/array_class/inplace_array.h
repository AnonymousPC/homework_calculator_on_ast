#pragma once

/// Class inplace_array

template < class type, int len >
class inplace_array
    extends public array_algo<inplace_array<type,len>,type>
{
    private: // Precondition
        static_assert ( not std::is_const<type>::value and not std::is_volatile<type>::value and not std::is_reference<type>::value );
        static_assert ( std::is_default_constructible<type>::value and std::is_move_assignable<type>::value );
        static_assert ( len >= 0 );

    private: // Data
        type data[len] = {};
        int  m         = 0;

    public: // Typedef
        using  value_type     = type;
        using  iterate_type   = type;
        using  iterator       = type*;
        using  const_iterator = const type*;
        using  array_algo     = array_algo<inplace_array,type>;
        struct array_tag { };

    public: // Core
        constexpr          inplace_array ( ) = default;
        constexpr          inplace_array ( const inplace_array&  )                                     requires std::is_copy_assignable<type>::value;
        constexpr          inplace_array (       inplace_array&& );
        constexpr explicit inplace_array ( int );
        constexpr          inplace_array ( int,  const type& )                                         requires std::is_copy_assignable<type>::value;
        constexpr          inplace_array ( int,  function_type<type()   > auto );
        constexpr          inplace_array ( int,  function_type<type(int)> auto );
        constexpr          inplace_array (       std::initializer_list<type>&& );
        constexpr          inplace_array ( const array_type<type> auto& )                              requires std::is_copy_assignable<type>::value;
        constexpr          inplace_array ( const range_type<type> auto& )                              requires std::is_copy_assignable<type>::value;
        constexpr          inplace_array ( std::from_range_t, std::ranges::input_range auto&& r )      requires requires { std::declval<inplace_array>().push(*r.begin()); };
        constexpr          inplace_array ( std::from_range_t, std::ranges::input_range auto&& r, int ) requires requires { std::declval<inplace_array>().push(*r.begin()); };
        constexpr          inplace_array& operator = ( const inplace_array&  )                         requires std::is_copy_assignable<type>::value;
        constexpr          inplace_array& operator = (       inplace_array&& );

    public: // Conversion
        template <              int len2 > constexpr          inplace_array ( const inplace_array<type, len2>&  ) requires ( len != len2 and std::is_copy_assignable<type>::value );
        template <              int len2 > constexpr          inplace_array (       inplace_array<type, len2>&& ) requires ( len != len2 );
        template < class type2, int len2 > constexpr          inplace_array ( const inplace_array<type2,len2>&  ) requires ( std::is_convertible<type2,type>::value but not std::is_same<type,type2>::value );
        template < class type2, int len2 > constexpr explicit inplace_array ( const inplace_array<type2,len2>&  ) requires ( std::is_constructible<type,type2>::value but not std::is_convertible<type2,type>::value );

    public: // Interface
        constexpr        int            size        ( )     const;
        constexpr static int            capacity    ( );
        constexpr        bool           empty       ( )     const;
        constexpr        inplace_array& resize      ( int );
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

#include "inplace_array.cpp"
