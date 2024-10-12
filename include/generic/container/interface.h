#pragma once
#include "../basic/interface.h"

namespace ap
{
    /// Class
    template < class type, int dim = 1 >                                        class array;
    template < class type >                                                     using vector = array<type>;
    template < class type >                                                     using matrix = array<type,2>;
    template < class type, int len >                                            class static_array;
    template < class type, int len >                                            using static_vector  = static_array<type,len>;
    template < class type, int len >                                            class inplace_array;
    template < class type, int len >                                            using inplace_vector = inplace_array<type,len>;

    template < class type >                                                     class deque;
    template < class type >                                                     class list;
    template < class type, class compare = std::less<type> >                    class priority_queue;
    template < class type >                                                     class queue;
    template < class type >                                                     class stack;

    template < class type,  class compare, class container >                    class basic_set;
    template < class type1, class type2,   class key_compare, class container > class basic_map;

    template < class type1, class type2 = type1 >                               class pair;
    template < class... types >                                                 class tuple;

                                                                                class any;
    template < class type >                                                     class function;
    template < class type >                                                     class optional;
    template < class... types >                                                 class property_tree;
    template < class... types >                                                 class variant;

    template < class char_type >                                                class basic_string;
                                                                                using string    = basic_string<char>;
                                                                                using wstring   = basic_string<wchar_t>;
                                                                                using u8string  = basic_string<char8_t>;
                                                                                using u16string = basic_string<char16_t>;
                                                                                using u32string = basic_string<char32_t>;
    template < class char_type >                                                class basic_string_view;
                                                                                using string_view    = basic_string_view<char>;
                                                                                using wstring_view   = basic_string_view<wchar_t>;
                                                                                using u8string_view  = basic_string_view<char8_t>;
                                                                                using u16string_view = basic_string_view<char16_t>;
                                                                                using u32string_view = basic_string_view<char32_t>;
    template < class char_type >                                                class basic_regex;
                                                                                using regex       = basic_regex<char>;
                                                                                using wregex      = basic_regex<wchar_t>;


    template < auto... digits >                                                 class constexpr_index;



    /// Concept
    // template < class input_type, class value_type = void, int dim = 0 >           concept array_type          = ...;
    // template < class input_type, class value_type = void >                        concept deque_type          = ...;
    // template < class input_type, class value_type = void >                        concept list_type           = ...;
    // template < class input_type, class value_type = void >                        concept priority_queue_type = ...;
    // template < class input_type, class value_type = void >                        concept queue_type          = ...;
    // template < class input_type, class value_type = void >                        concept stack_type          = ...;
    // template < class input_type, class key_type = void, class value_type = void > concept pair_type           = ...;
    // template < class input_type, class... value_types >                           concept tuple_type          = ...;
    // template < class input_type, class value_type = void >                        concept set_type            = ...;
    // template < class input_type, class key_type = void, class value_type = void > concept map_type            = ...;
    // template < class input_type, class char_type = void >                         concept string_type         = ...;
    // template < class input_type, class char_type = void >                         concept general_string_type = ...;

    /// Include
    #include "discrete/discrete.h" // First.
    #include "array/array.h"
    #include "chain/chain.h"
    #include "collection/collection.h"
    #include "polymorphic/polymorphic.h"
    #include "string/string.h"
    #include "utility/utility.h"

    /// Literal
    namespace literals
    {
        template < char... index >
        constexpr auto           operator ""c   ( )                                { return constexpr_index<index...>();  }
        constexpr string         operator ""s   ( const char*     ptr, size_t    ) { return string         ( ptr     );   }
        constexpr wstring        operator ""s   ( const wchar_t*  ptr, size_t    ) { return wstring        ( ptr     );   }
        constexpr u8string       operator ""s   ( const char8_t*  ptr, size_t    ) { return u8string       ( ptr     );   }
        constexpr u16string      operator ""s   ( const char16_t* ptr, size_t    ) { return u16string      ( ptr     );   }
        constexpr u32string      operator ""s   ( const char32_t* ptr, size_t    ) { return u32string      ( ptr     );   }
        constexpr string_view    operator ""sv  ( const char*     ptr, size_t sz ) { return string_view    ( ptr, sz );   }
        constexpr wstring_view   operator ""sv  ( const wchar_t*  ptr, size_t sz ) { return wstring_view   ( ptr, sz );   }
        constexpr u8string_view  operator ""sv  ( const char8_t*  ptr, size_t sz ) { return u8string_view  ( ptr, sz );   }
        constexpr u16string_view operator ""sv  ( const char16_t* ptr, size_t sz ) { return u16string_view ( ptr, sz );   }
        constexpr u32string_view operator ""sv  ( const char32_t* ptr, size_t sz ) { return u32string_view ( ptr, sz );   }
        constexpr regex          operator ""rgx ( const char*     ptr, size_t sz ) { return regex (string_view (ptr,sz)); }
        constexpr wregex         operator ""rgx ( const wchar_t*  ptr, size_t sz ) { return wregex(wstring_view(ptr,sz)); }
    }

} // namespace ap










