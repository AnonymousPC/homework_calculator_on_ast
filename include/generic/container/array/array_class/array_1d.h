#pragma once

/// Class array

template < class type >
class array<type>
    extends public array_algo<array<type>,type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> or requires { type(); } );                    // Sometimes default-constructor are only friend to array.
        static_assert ( std::movable<type> or requires { type(std::move(std::declval<type&&>())); } ); // Sometimes move-assignor       are only friend to array.

    private: // Data
        int   m    = 0;
        type* data = allocate ( size() );

    public: // Typedef
        using  value_type     = type;
        using  iterate_type   = type;
        using  iterator       = type*;
        using  const_iterator = const type*;
        using  array_algo     = array_algo<array<type>,type>;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )                                             requires std::copyable<type>;
        constexpr          array (       array&& );
        constexpr explicit array ( int );
        constexpr          array ( int,  const type& )                                         requires std::copyable<type>;
        constexpr          array ( int,  function_type<type()   > auto );
        constexpr          array ( int,  function_type<type(int)> auto );
        constexpr          array (       std::initializer_list<type>&& );
        constexpr          array ( const array_type<type,1> auto& )                            requires std::copyable<type>;
        constexpr          array ( const array_type         auto& arr )                        requires ( not std::same_as<typename decay<decltype(arr)>::value_type,type> ) but std::convertible_to<typename decay<decltype(arr)>::value_type,type> and ( decay<decltype(arr)>::dimension() == 1 );
        constexpr          array ( const range_type<type>   auto& )                            requires std::copyable<type>;
        constexpr          array ( const range_type         auto& rg )                         requires ( not std::same_as<typename decay<decltype(rg )>::value_type,type> ) but std::convertible_to<typename decay<decltype(rg )>::value_type,type>;
        constexpr          array ( std::from_range_t, std::ranges::input_range auto&& r )      requires requires { std::declval<array>().push(*r.begin()); };
        constexpr          array ( std::from_range_t, std::ranges::input_range auto&& r, int ) requires requires { std::declval<array>().push(*r.begin()); };
        constexpr         ~array ( );
        constexpr          array& operator = ( const array&  )                                 requires std::copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Conversion
        template < class type2 > constexpr          array ( const array<type2>& )              requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array<type2>& )              requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

   public: // Interface
        constexpr       void           row         ( )    = delete;
        constexpr       int            size        ( )      const;
        constexpr       bool           empty       ( )      const;
        constexpr       array&         resize      ( int );
        constexpr       iterator       begin       ( );
        constexpr       const_iterator begin       ( )      const;
        constexpr       iterator       end         ( );
        constexpr       const_iterator end         ( )      const;
        constexpr       type&          operator [] ( int );
        constexpr const type&          operator [] ( int )  const;

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten;

    private: // Auxiliary
        constexpr static type* allocate   ( int   );
        constexpr static void  deallocate ( type* );
        constexpr static int   capacity   ( int   );
};


#include "array_1d.cpp"

