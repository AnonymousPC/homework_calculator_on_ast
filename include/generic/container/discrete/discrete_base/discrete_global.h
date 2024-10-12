#pragma once

#define left_type                 decay<decltype(left )>
#define left_key_type    typename decay<decltype(left )>::key_type
#define left_value_type  typename decay<decltype(left )>::value_type
#define right_type                decay<decltype(right)>
#define right_key_type   typename decay<decltype(right)>::key_type
#define right_value_type typename decay<decltype(right)>::value_type

/// Auxiliary

namespace aux
{
    template < class type, int count = 1 >
    constexpr bool tuplewise_printable =
        printable<tuple_element<count,type>> and []
        {
            if constexpr ( count < tuple_size<type> )
                return tuplewise_printable<type,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_equalable =
        tuple_size<type1> == tuple_size<type2> and
        equalable_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_equalable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_comparable =
        tuple_size<type1> == tuple_size<type2> and
        comparable_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_comparable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_addable =
        tuple_size<type1> == tuple_size<type2> and
        addable_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_addable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_minusable =
        tuple_size<type1> == tuple_size<type2> and
        minusable_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_minusable<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_convertible =
        tuple_size<type1> == tuple_size<type2> and
        std::convertible_to<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_convertible<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_same =
        tuple_size<type1> == tuple_size<type2> and
        std::same_as<tuple_element<count,type1>,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_same<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_multipliable_to =
        multipliable_to<tuple_element<count,type1>,type2> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_each_multipliable_to<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_multipliable_to_each =
        multipliable_to<type1,tuple_element<count,type2>> and []
        {
            if constexpr ( count < tuple_size<type2> )
                return tuplewise_multipliable_to_each<type1,type2,count+1>;
            else
                return true;
        } ();

    template < class type1, class type2, int count = 1 >
    constexpr bool tuplewise_each_dividable_to =
        multipliable_to<tuple_element<count,type1>,type2> and []
        {
            if constexpr ( count < tuple_size<type1> )
                return tuplewise_each_dividable_to<type1,type2,count+1>;
            else
                return true;
        } ();

} // namespace aux


/// Concept

template < class input_type, class type1 = void, class type2 = void >
concept pair_type = []
{
    static_assert ( std::is_void<type1>::value == std::is_void<type2>::value, "must enable or disable both key/value type check at the same time" );
    if constexpr ( requires { typename input_type::pair_tag; } )
    {
        static_assert ( requires { typename input_type::key_type; typename input_type::value_type; }, "class provides pair_tag but not provides key_type and value_type" );
        if constexpr ( not std::is_void<type1>::value and not std::is_void<type2>::value )
            return std::same_as<typename input_type::key_type,type1> and std::same_as<typename input_type::value_type,type2>;
        else
            return true;
    }
    else
        return false;
} ();


template < class input_type, class... types >
concept tuple_type = []
{
    if constexpr ( requires { typename input_type::tuple_tag; } )
    {
        static_assert ( requires { typename input_type::value_type<1>; typename input_type::value_type<input_type::size()>; input_type::size(); }, "class provides tuple_tag but not provides value_type and size()" );
        if constexpr ( sizeof...(types) != 0 )
            return aux::tuplewise_same<input_type,tuple<types...>>;
        else
            return true;
    }
    else
        return false;
} ();




/// Global


constexpr            std::ostream& operator <<  ( std::ostream& left,         const pair_type auto& right ) requires printable      <right_key_type>               and printable      <right_value_type>;
constexpr            bool          operator ==  ( const pair_type auto& left, const pair_type auto& right ) requires equalable_to   <left_key_type,right_key_type> and equalable_to   <left_value_type,right_value_type>;
constexpr            auto          operator <=> ( const pair_type auto& left, const pair_type auto& right ) requires comparable_to  <left_key_type,right_key_type> and comparable_to  <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  +  ( const pair_type auto& left, const pair_type auto& right ) requires addable_to     <left_key_type,right_key_type> and addable_to     <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  -  ( const pair_type auto& left, const pair_type auto& right ) requires minusable_to   <left_key_type,right_key_type> and minusable_to   <left_value_type,right_value_type>;
constexpr pair_type  auto          operator  *  ( const pair_type auto& left, const           auto& right ) requires multipliable_to<left_key_type,right_type>     and multipliable_to<left_value_type,right_type>       but ( not pair_type<right_type> );
constexpr pair_type  auto          operator  *  ( const           auto& left, const pair_type auto& right ) requires multipliable_to<left_type,    right_key_type> and multipliable_to<left_type,      right_value_type> but ( not pair_type<left_type>  );
constexpr pair_type  auto          operator  /  ( const pair_type auto& left, const           auto& right ) requires dividable_to   <left_key_type,right_type>     and dividable_to   <left_value_type,right_type>       but ( not pair_type<right_type> );


constexpr            std::ostream& operator <<  ( std::ostream& left,          const tuple_type auto& right ) requires aux::tuplewise_printable           <right_type>;
constexpr            bool          operator ==  ( const tuple_type auto& left, const tuple_type auto& right ) requires aux::tuplewise_equalable           <left_type,right_type>;
constexpr            auto          operator <=> ( const tuple_type auto& left, const tuple_type auto& right ) requires aux::tuplewise_comparable          <left_type,right_type>;
constexpr tuple_type auto          operator  +  ( const tuple_type auto& left, const tuple_type auto& right ) requires aux::tuplewise_addable             <left_type,right_type>;
constexpr tuple_type auto          operator  -  ( const tuple_type auto& left, const tuple_type auto& right ) requires aux::tuplewise_minusable           <left_type,right_type>;
constexpr tuple_type auto          operator  *  ( const tuple_type auto& left, const            auto& right ) requires aux::tuplewise_each_multipliable_to<left_type,right_type> but ( not tuple_type<right_type> );
constexpr tuple_type auto          operator  *  ( const            auto& left, const tuple_type auto& right ) requires aux::tuplewise_multipliable_to_each<left_type,right_type> but ( not tuple_type<left_type > );
constexpr tuple_type auto          operator  /  ( const tuple_type auto& left, const            auto& right ) requires aux::tuplewise_each_dividable_to   <left_type,right_type> but ( not tuple_type<right_type> );


#include "discrete_global.cpp"
#undef left_type
#undef left_key_type
#undef left_value_type
#undef right_type
#undef right_key_type
#undef right_value_type
