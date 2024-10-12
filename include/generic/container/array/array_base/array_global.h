#pragma once

#define left_value_type  typename decay<decltype(left )>::value_type
#define right_value_type typename decay<decltype(right)>::value_type




/// Concept

template < class input_type, class value_type = void, int dim = 0 >
concept array_type = []
{
    if constexpr ( requires { typename input_type::array_tag; } )
    {
        static_assert ( requires { typename input_type::value_type; input_type::dimension(); }, "class provides array_tag but not provides value_type or dimension()" );
        if constexpr ( is_void<value_type> and dim == 0 )
            return true;
        else if constexpr ( is_void<value_type> and dim != 0 )
            static_assert ( false, "cannot only check dimension but not check value_type");
        else if constexpr ( not is_void<value_type> and dim == 0 )
            return std::same_as<typename input_type::value_type,value_type>;
        else if constexpr ( not is_void<value_type> and dim != 0 )
            return std::same_as<typename input_type::value_type,value_type> and input_type::dimension() == dim;
    }
    else
        return false;
} ();





/// Global ( For linear math, see "root/math/linear". )

constexpr std::ostream& operator << ( std::ostream& left, const array_type auto& right ) requires printable<right_value_type>;






/// Auxiliary

namespace aux
{
    template < class input_type, class value_type, int min, int max >
    constexpr bool array_type_dim_range_helper = []
    {
        if constexpr ( min < 1 )
            return std::convertible_to<input_type,value_type> or array_type_dim_range_helper<input_type,value_type,1,max>;
        else if constexpr ( requires { input_type::dimension(); } )
            return array_type<input_type,value_type> and input_type::dimension() >= min and input_type::dimension() <= max;
        else
            return false;
    } () or requires { typename input_type::string_tag; }; // As this concept is used iff in basic functions like push() and pop(), here we allow it to string.

    template < class input_type, class value_type, int min, int max >
    concept array_type_dim_range = array_type_dim_range_helper<input_type,value_type,min,max>;

    template < class type, class... types >
    constexpr bool ints_until_last_func = []
    {
        if constexpr ( std::is_void<type>::value )
            return ap::convertible_until<int,-2,types...> and std::invocable<ap::last_type_of<types...>>;
        else
            return ap::convertible_until<int,-2,types...> and ap::function_type<ap::last_type_of<types...>,type()>;
    } ();

    template < class result_type, class input_type, int count, class... types >
    constexpr bool invocable_r_by_n_ints_helper = []
    {
        if constexpr ( count >= 1 )
            return invocable_r_by_n_ints_helper<result_type,input_type,count-1,int,types...>;
        else
            if constexpr ( std::is_void<result_type>::value )
                return std::invocable<input_type,types...>;
            else
                return ap::function_type<input_type,result_type(types...)>;
    } ();

    template < class result_type, class input_type, int count >
    constexpr bool invocable_r_by_n_ints = invocable_r_by_n_ints_helper<result_type,input_type,count>;

    template < class type, class... types >
    constexpr bool ints_until_last_func_ints = ap::convertible_until<int,-2,types...> and invocable_r_by_n_ints<type,ap::last_type_of<types...>,sizeof...(types)-1>; // No need to check <void,...>, as it forwards to is_invocable_r_by_n_ints.

    template < class type, class... types >
    constexpr bool ints_until_last_type = ap::convertible_until<int,-2,types...> and []
    {
        if constexpr ( std::is_void<type>::value )
            return not ints_until_last_func<type,types...> and not ints_until_last_func_ints<type,types...>;
        else
            return std::convertible_to<ap::last_type_of<types...>,type>;
    } ();

    template < class input_type, int count, class... types >
    struct invoke_result_by_n_ints_helper;

    template < class input_type, int count, class... types >
        requires ( count >= 1 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result_by_n_ints_helper<input_type,count-1,int,types...>::type;
    };

    template < class input_type, int count, class... types >
        requires ( count == 0 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result<input_type,types...>;
    };

    template < class input_type, int count >
    using invoke_result_by_n_ints = invoke_result_by_n_ints_helper<input_type,count>::type;                                                                  // Helper
}




/// Template deduction
                                                   array ( array_type auto arr )
                                                -> array<typename decltype(arr)::value_type,decltype(arr)::dimension()>;

                                                   array ( auto... args )
                                                -> array<last_type_of<decltype(args)...>,sizeof...(args)-1>
                                                       requires ( sizeof...(args) >= 2 ) and
                                                                aux::ints_until_last_type<void,decltype(args)...> and
                                                                ( not std::convertible_to<last_type_of<decltype(args)...>,int> ); // Last_type = int is ambiguous.

                                                   array ( auto... args )
                                                -> array<invoke_result<last_type_of<decltype(args)...>>,sizeof...(args)-1>
                                                       requires ( sizeof...(args) >= 2 ) and
                                                                aux::ints_until_last_func<void,decltype(args)...>;

                                                   array ( auto... args )
                                                -> array<aux::invoke_result_by_n_ints<last_type_of<decltype(args)...>,sizeof...(args)-1>,sizeof...(args)-1>
                                                       requires ( sizeof...(args) >= 2 ) and
                                                                aux::ints_until_last_func_ints<void,decltype(args)...>;

template < class type >                            array ( std::initializer_list<type> )
                                                -> array<type>;

template < class type >                            array ( std::initializer_list<std::initializer_list<type>> )
                                                -> array<type,2>;

template < class type, int dim >                   array ( std::initializer_list<array<type,dim>> )
                                                -> array<type,dim+1>;

template < class type, bool continuous >           array ( range<type,continuous> )
                                                -> array<type>;



template < class type >                            static_array ( type, std::same_as<type> auto... args )
                                                -> static_array<type,1+sizeof...(args)>;

template < class type >                            inplace_array ( type, std::same_as<type> auto... args )
                                                -> inplace_array<type,1+sizeof...(args)>;




#include "array_global.cpp"

#undef left_value_type
#undef right_value_type
