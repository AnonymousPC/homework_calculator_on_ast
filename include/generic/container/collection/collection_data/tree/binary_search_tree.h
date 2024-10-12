#pragma once

template < class type, class compares >
class binary_search_tree
    extends public binary_tree<type>
{
    protected: // Class
        using node = binary_tree<type>::node;

    public: // Typedef
        using value_type     = type;
        using const_iterator = binary_tree<type>::const_iterator;

    public: // Interface
        using binary_tree<type>::size,
              binary_tree<type>::empty,
              binary_tree<type>::begin,
              binary_tree<type>::end,
              binary_tree<type>::min,
              binary_tree<type>::mid,
              binary_tree<type>::max,
              binary_tree<type>::clear;

        constexpr const_iterator locate ( const auto&  val )                                    const requires requires { compares::equal_to(val,std::declval<type>()); };
        constexpr const_iterator push   (       auto&& val, const_iterator = const_iterator() )       requires std::convertible_to<decltype(val),type>;
        constexpr const_iterator pop    ( const auto&  val, const_iterator = const_iterator() )       requires requires { compares::equal_to(val,std::declval<type>()); };

    private: // Auxiliary
        constexpr const_iterator pop_leaf   ( const_iterator );
        constexpr const_iterator pop_branch ( const_iterator );
        constexpr const_iterator pop_crotch ( const_iterator );
};



#include "binary_search_tree.cpp"

