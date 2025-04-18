#pragma once

#define left_key_type          typename decay<decltype(left )>::key_type
#define left_value_type        typename decay<decltype(left )>::value_type
#define left_compare_type      typename decay<decltype(left )>::compare_type
#define left_key_compare_type  typename decay<decltype(left )>::key_compare_type
#define right_key_type         typename decay<decltype(right)>::key_type
#define right_value_type       typename decay<decltype(right)>::value_type
#define right_compare_type     typename decay<decltype(right)>::compare_type
#define right_key_compare_type typename decay<decltype(right)>::key_compare_type



/// Concept

template < class input_type, class value_type = void >
concept set_type = []
{
    if constexpr ( requires { typename input_type::set_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides set_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();

template < class input_type, class key_type = void, class value_type = void >
concept map_type = []
{
    static_assert ( is_void<key_type> == is_void<value_type>, "must enable or disable both key/value type check at the same time" );
    if constexpr ( requires { typename input_type::map_tag; } )
    {
        static_assert ( requires { typename input_type::key_type; typename input_type::value_type; }, "class provides map_tag but not provides key_type and value_type" );
        if constexpr ( is_void<key_type> and is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::key_type,key_type> and std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();




/// Global

constexpr          std::ostream&  operator <<  (       std::ostream&  left, const set_type auto& right ) requires printable<right_value_type>;
constexpr          bool           operator ==  ( const set_type auto& left, const set_type auto& right ) requires equalable_to <left_value_type,right_value_type>;
constexpr          auto           operator <=> ( const set_type auto& left, const set_type auto& right ) requires comparable_to<left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr          bool           operator <<  ( const set_type auto& left, const set_type auto& right ) requires equalable_to <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr          bool           operator >>  ( const set_type auto& left, const set_type auto& right ) requires equalable_to <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr set_type auto           operator  +  ( const set_type auto& left, const set_type auto& right ) requires std::same_as <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr set_type auto           operator  -  ( const set_type auto& left, const set_type auto& right ) requires std::same_as <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr set_type auto           operator  |  ( const set_type auto& left, const set_type auto& right ) requires std::same_as <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr set_type auto           operator  &  ( const set_type auto& left, const set_type auto& right ) requires std::same_as <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr set_type auto           operator  ^  ( const set_type auto& left, const set_type auto& right ) requires std::same_as <left_value_type,right_value_type> and std::same_as<left_compare_type,right_compare_type>;
constexpr set_type auto&          operator  += (       set_type auto& left, const set_type auto& right ) requires requires { left = left + right; };
constexpr set_type auto&          operator  -= (       set_type auto& left, const set_type auto& right ) requires requires { left = left - right; };
constexpr set_type auto&          operator  |= (       set_type auto& left, const set_type auto& right ) requires requires { left = left | right; };
constexpr set_type auto&          operator  &= (       set_type auto& left, const set_type auto& right ) requires requires { left = left & right; };
constexpr set_type auto&          operator  ^= (       set_type auto& left, const set_type auto& right ) requires requires { left = left ^ right; };

constexpr          std::ostream&  operator <<  (       std::ostream&  left, const map_type auto& right ) requires printable<right_key_type>                  and printable<right_value_type>;
constexpr          bool           operator ==  ( const map_type auto& left, const map_type auto& right ) requires equalable_to <left_key_type,right_key_type> and equalable_to <left_value_type,right_value_type>;
constexpr          auto           operator <=> ( const map_type auto& left, const map_type auto& right ) requires comparable_to<left_key_type,right_key_type> and comparable_to<left_value_type,right_value_type> and std::same_as<left_key_compare_type,right_key_compare_type>;


#include "collection_global.cpp"

#undef left_key_type
#undef left_value_type
#undef left_compare_type
#undef left_key_compare_type
#undef right_key_type
#undef right_value_type
#undef right_compare_type
#undef right_key_compare_type
