#pragma once

template < class type1, class type2 >
class pair
{
    public: // Typedef
        using  key_type   = type1;
        using  value_type = type2;
        struct pair_tag { };

    private: // Data
        type1 x = type1();
        type2 y = type2();

    public: // Core
        constexpr  pair ( )                            requires ( std::is_constructible<type1>::value and std::is_constructible<type2>::value ) = default;
        constexpr  pair ( type1, type2 );
        constexpr  pair ( const pair&  )             = default;
        constexpr  pair (       pair&& )             = default;
        constexpr ~pair ( )                          = default;
        constexpr  pair& operator = ( const pair&  ) = default;
        constexpr  pair& operator = (       pair&& ) = default;
        constexpr        type1& key   ( );
        constexpr  const type1& key   ( ) const;
        constexpr        type2& value ( );
        constexpr  const type2& value ( ) const;

    public: // Conversion
        template < class type3, class type4 > constexpr          pair ( const pair<type3,type4>& ) requires ( std::is_convertible<type3,type1>::value and std::is_convertible<type4,type2>::value but not ( std::is_same<type1,type3>::value and std::is_same<type2,type4>::value ) );
        template < class type3, class type4 > constexpr explicit pair ( const pair<type3,type4>& ) requires ( std::is_constructible<type1,type3>::value and std::is_constructible<type2,type4>::value but ( not std::is_convertible<type3,type1>::value or not std::is_convertible<type4,type2>::value ) );

    protected: // For map_pair
        template < class type3, class type4 > constexpr explicit pair ( pair<type3,type4>&& ) requires ( ( ( std::is_const<type1>::value and std::is_same<typename std::decay<type1>::type,typename std::decay<type3>::type>::value ) or ( std::is_const<type2>::value and std::is_same<typename std::decay<type2>::type,typename std::decay<type4>::type>::value ) ) and ( not std::is_lvalue_reference<type3>::value and not std::is_lvalue_reference<type4>::value ) );

};


/// Template deduction

template < class type1, class type2 > pair ( type1, type2 ) -> pair<type1,type2>;



#include "pair.cpp"
