#pragma once

#define left_type        decay<decltype(left )>
#define right_type       decay<decltype(right)>
#define left_value_type  typename decltype(basic_string_view(left ))::value_type
#define right_value_type typename decltype(basic_string_view(right))::value_type

/// Concept

template < class input_type, class value_type = void >
concept string_type = []
{
    if constexpr ( requires { typename input_type::string_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides string_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();

template < class input_type, class value_type = void >
concept general_string_type = char_type<input_type> or
                              char_type<remove_extent<input_type>> or
                              char_type<remove_pointer<input_type>> or
                              string_type<input_type>;



/// Global

constexpr std::istream& operator >> ( std::istream& left,       string_type auto& right );
constexpr std::ostream& operator << ( std::ostream& left, const string_type auto& right );

constexpr             bool          operator ==  ( const general_string_type auto& left, const general_string_type auto& right ) requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>;
constexpr             auto          operator <=> ( const general_string_type auto& left, const general_string_type auto& right ) requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>;
constexpr string_type auto          operator  +  ( const general_string_type auto& left, const general_string_type auto& right ) requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>;
constexpr string_type auto&         operator  += (       general_string_type auto& left, const general_string_type auto& right ) requires std::same_as<left_type,basic_string<left_value_type>> and std::same_as<left_value_type,right_value_type>;

constexpr string_type auto          operator  *  ( const string_type auto&, int_type auto );
constexpr string_type auto          operator  *  ( int_type auto, const string_type auto& );
constexpr string_type auto&         operator  *= (       string_type auto&, int_type auto );

#include "string_global.cpp"

#undef left_type
#undef right_type
#undef left_value_type
#undef right_value_type
