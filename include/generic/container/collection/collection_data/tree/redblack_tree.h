#pragma once

template < class type, class compares >
class redblack_tree
    extends public binary_search_tree<type,compares>
{
    protected: // Class
        using node = binary_search_tree<type,compares>::node;
        constexpr static const int red   = 0;
        constexpr static const int black = 1;

    public: // Typedef
        using value_type     = type;
        using const_iterator = binary_search_tree<type,compares>::const_iterator;

    public: // Interface
        using binary_search_tree<type,compares>::size,
              binary_search_tree<type,compares>::empty,
              binary_search_tree<type,compares>::begin,
              binary_search_tree<type,compares>::end,
              binary_search_tree<type,compares>::min,
              binary_search_tree<type,compares>::mid,
              binary_search_tree<type,compares>::max,
              binary_search_tree<type,compares>::clear,
              binary_search_tree<type,compares>::locate;

        constexpr const_iterator push   (       auto&& val, const_iterator = const_iterator() ) requires std::convertible_to<decltype(val),type>;
        constexpr const_iterator pop    ( const auto&  val, const_iterator = const_iterator() ) requires requires { compares::equal_to(val,std::declval<type>()); };

    private: // Auxiliary
        constexpr void push_balance                ( const_iterator ); // Note: input node must be red.
        constexpr void push_balance_combine_red    ( const_iterator );
        constexpr void push_balance_same_direction ( const_iterator );
        constexpr void push_balance_diff_direction ( const_iterator );
        constexpr void pop_balance                 ( const_iterator );
        constexpr void left_rotate                 ( const_iterator );
        constexpr void right_rotate                ( const_iterator );
};

#include "redblack_tree.cpp"
