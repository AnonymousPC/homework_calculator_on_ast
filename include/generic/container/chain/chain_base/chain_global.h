#pragma once

/// Declaration ( concept )

template < class input_type, class value_type = void >
concept deque_type = []
{
    if constexpr ( requires { typename input_type::deque_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides deque_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();

template < class input_type, class value_type = void >
concept list_type = []
{
    if constexpr ( requires { typename input_type::list_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides list_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();

template < class input_type, class value_type = void >
concept priority_queue_type = []
{
    if constexpr ( requires { typename input_type::priority_queue_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides priority_queue_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();

template < class input_type, class value_type = void >
concept queue_type = []
{
    if constexpr ( requires { typename input_type::queue_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides queue_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();

template < class input_type, class value_type = void >
concept stack_type = []
{
    if constexpr ( requires { typename input_type::stack_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; }, "class provides stack_tag but not provides value_type" );
        if constexpr ( is_void<value_type> )
            return true;
        else
            return std::same_as<typename input_type::value_type,value_type>;
    }
    else
        return false;
} ();
