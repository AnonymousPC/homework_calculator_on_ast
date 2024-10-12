#pragma once
#define color() info()
#define top()   ( *const_cast<node*> ( static_cast<const node*> ( mid() ) ) )

/// Class redblack_tree

// Member

template < class type, class compares >
constexpr redblack_tree<type,compares>::const_iterator redblack_tree<type,compares>::push ( auto&& val, const_iterator it )
    requires std::convertible_to<decltype(val),type>
{
    if ( size() == 0 )
        top().color() = black; // In default constructor it's red, we turn it into black the first time we push in new nodes.

    let unbalanced = binary_search_tree<type,compares>::push ( std::move ( val ), it );
    push_balance ( unbalanced );
    top().color() = black;
    return unbalanced;
}

template < class type, class compares >
constexpr redblack_tree<type,compares>::const_iterator redblack_tree<type,compares>::pop ( const auto& val, const_iterator it )
    requires requires { compares::equal_to(val,std::declval<type>()); }
{
    let unbalanced = binary_search_tree<type,compares>::pop ( val, it );
    top().color() = black;
    pop_balance ( unbalanced );
    return unbalanced;
}

// Auxiliary

template < class type, class compares >
constexpr void redblack_tree<type,compares>::push_balance ( const_iterator it ) // Note: color must be red.
{
    node& nd = *const_cast<node*> ( static_cast<const node*> ( it ) );

    if ( nd.up().color() == black )
        return;

    // Now nd.color() == red and nd.up().color() == red, where conflicts happens.

    if ( nd.up().has_another() and nd.up().another().color() == red )
        return push_balance_combine_red ( &nd );

    else if ( nd.is_left() == nd.up().is_left() )
        return push_balance_same_direction ( &nd );

    else
        return push_balance_diff_direction ( &nd );
}

template < class type, class compares >
constexpr void redblack_tree<type,compares>::push_balance_combine_red ( const_iterator it )
{
    node& nd = *const_cast<node*> ( static_cast<const node*> ( it ) );

    nd.up()           .color() = black;
    nd.up().another() .color() = black;
    nd.up().up()      .color() = red;

    return push_balance ( &nd.up().up() );
}

template < class type, class compares >
constexpr void redblack_tree<type,compares>::push_balance_same_direction ( const_iterator it )
{
    node& nd = *const_cast<node*> ( static_cast<const node*> ( it ) );

    nd.is_left() ? right_rotate ( &nd.up() ) otherwise left_rotate ( &nd.up() );
    nd.up()     .color() = black;
    nd.another().color() = red;

    return;
}

template < class type, class compares >
constexpr void redblack_tree<type,compares>::push_balance_diff_direction ( const_iterator it )
{
    node& nd = *const_cast<node*> ( static_cast<const node*> ( it ) );

    if ( nd.is_left() )
    {
        right_rotate ( &nd );
        return push_balance_same_direction ( &nd.right() );
    }

    else
    {
        left_rotate ( &nd );
        return push_balance_same_direction ( &nd.left() );
    }
}

template < class type, class compares >
constexpr void redblack_tree<type,compares>::pop_balance ( const_iterator )
{
    return;
}


template < class type, class compares >
constexpr void redblack_tree<type,compares>::left_rotate ( const_iterator it )
{
    node& axis = *const_cast<node*> ( static_cast<const node*> ( it ) );

    #if debug
        if ( axis.is_left() or not axis.up().has_up() )
            throw nullptr_error();
    #endif

    bool flag = axis.up().is_left();

    node& a     = axis.up().cut_up();
    node& b     = axis.cut_up();
    node* c_ptr = axis.has_left() ? &axis.cut_left() otherwise nullptr;

    flag ? a.link_left ( axis ) otherwise a.link_right ( axis );
    axis.link_left ( b );

    if ( c_ptr != nullptr )
        b.link_right ( *c_ptr );
}

template < class type, class compares >
constexpr void redblack_tree<type,compares>::right_rotate ( const_iterator it )
{
    node& axis = *const_cast<node*> ( static_cast<const node*> ( it ) );

    #if debug
        if ( axis.is_right() or not axis.up().has_up() )
            throw nullptr_error();
    #endif

    bool flag = axis.up().is_right();

    node& a     = axis.up().cut_up();
    node& b     = axis.cut_up();
    node* c_ptr = axis.has_right() ? &axis.cut_right() otherwise nullptr;

    flag ? a.link_right ( axis ) otherwise a.link_left ( axis );
    axis.link_right ( b );

    if ( c_ptr != nullptr )
        b.link_left ( *c_ptr );
}


#undef color
#undef top
