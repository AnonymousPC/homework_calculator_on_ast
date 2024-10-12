#pragma once

template < class char_type >
class basic_regex
    extends public std::basic_regex<char_type>
{
    public: // Friend
        template < class char_type2, class string_type >
        friend class string_algo;

    public: // Core
        constexpr          basic_regex ( ) = default;
        constexpr explicit basic_regex ( const char_type* );
        constexpr explicit basic_regex ( const basic_string_view<char_type>& );
};

#include "string_regex.cpp"
