#pragma once

/// Class regex

// Core

template < class char_type >
constexpr basic_regex<char_type>::basic_regex ( const char_type* rgx )
    try extends std::basic_regex<char_type> ( rgx )
    {

    }
    catch ( std::regex_error& e )
    {
        throw regex_error("bad regex-grammar occured in {}: {}", rgx, e.what());
    }



template < class char_type >
constexpr basic_regex<char_type>::basic_regex ( const basic_string_view<char_type>& rgx )
    try extends std::basic_regex<char_type> ( rgx.begin(), rgx.size() )
    {

    }
    catch ( std::regex_error& e )
    {
        throw regex_error("bad regex-grammar occured in {}: {}", rgx, e.what());
    }

