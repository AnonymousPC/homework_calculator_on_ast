#pragma once

/// Class binary_tree

// Core

template < class type >
constexpr binary_tree<type>::binary_tree ( const binary_tree& init )
    extends m ( init.m )
{
    if ( not empty() )
    {
        let min_max = root.copy_tree ( init.root );
        ptr_min = &min_max.left ();
        ptr_max = &min_max.right();
    }
}

template < class type >
constexpr binary_tree<type>::binary_tree ( binary_tree&& init )
    extends m       ( std::exchange ( init.m,       0       ) ),
            ptr_min ( std::exchange ( init.ptr_min, nullptr ) ),
            ptr_max ( std::exchange ( init.ptr_max, nullptr ) )
{
    if ( init.root.has_left() )
        root.link_left  ( init.root.cut_left()  );

    if ( init.root.has_right() )
        root.link_right ( init.root.cut_right() );
}

template < class type >
constexpr binary_tree<type>& binary_tree<type>::operator = ( binary_tree right )
{
    std::swap ( m,       right.m       );
    std::swap ( ptr_min, right.ptr_min );
    std::swap ( ptr_max, right.ptr_max );
    root.root_swap ( right.root );

    return self;
}

// Interface

template < class type >
constexpr int binary_tree<type>::size ( ) const
{
    return m;
}

template < class type >
constexpr bool binary_tree<type>::empty ( ) const
{
    return size() == 0;
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::begin ( ) const
{
    return const_iterator ( empty() ? &root otherwise ptr_min );
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::end ( ) const
{
    return const_iterator ( &root );
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::max ( ) const
{
    return const_iterator ( ptr_max != nullptr ? ptr_max otherwise &root );
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::mid ( ) const
{
    return const_iterator ( not empty() ? &root.left() otherwise &root );
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::min ( ) const
{
    return const_iterator ( ptr_min != nullptr ? ptr_min otherwise &root );
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::clear ( )
{
    m = 0;
    if ( not empty() )
        root.left().delete_self();

    return const_iterator ( &root );
}


// Print

template < class type >
std::ostream& binary_tree<type>::print_tree ( std::ostream& str ) const
{
    return not empty() ? static_cast<const node*>(mid())->print_tree(str) otherwise str;
}

// Auxiliary

template < class type >
constexpr int& binary_tree<type>::get_size ( )
{
    return m;
}

template < class type >
constexpr const binary_tree<type>::node*& binary_tree<type>::get_min ( )
{
    return ptr_min;
}

template < class type >
constexpr const binary_tree<type>::node*& binary_tree<type>::get_max ( )
{
    return ptr_max;
}


/// Class binary_tree::node

// Core

template < class type >
constexpr binary_tree<type>::node::node ( std::convertible_to<type> auto&& init_data )
    extends data ( std::move ( init_data ) )
{

}

template < class type >
constexpr binary_tree<type>::node::node ( std::convertible_to<type> auto&& init_data, node* init_ptr_up, node* init_ptr_left, node* init_ptr_right, int init_flag )
    extends data      ( std::move ( init_data ) ),
            ptr_up    ( init_ptr_up    ),
            ptr_left  ( init_ptr_left  ),
            ptr_right ( init_ptr_right ),
            flag      ( init_flag      )
{

}

template < class type >
constexpr binary_tree<type>::node::~node ( )
{
    delete ptr_left;
    delete ptr_right;
}

// Conversion

template < class type >
constexpr binary_tree<type>::node::operator type& ( )
{
    return data;
}


template < class type >
constexpr binary_tree<type>::node::operator const type& ( ) const
{
    return data;
}

template < class type >
constexpr int& binary_tree<type>::node::info ( )
{
    return flag;
}

template < class type >
constexpr const int& binary_tree<type>::node::info ( ) const
{
    return flag;
}

// Interface

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::up ( )
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return *ptr_up;
}

template < class type >
constexpr const binary_tree<type>::node& binary_tree<type>::node::up ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return *ptr_up;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::left ( )
{
    #if debug
        if ( not has_left() )
            throw nullptr_error();
    #endif
    return *ptr_left;
}

template < class type >
constexpr const binary_tree<type>::node& binary_tree<type>::node::left ( ) const
{
    #if debug
        if ( not has_left() )
            throw nullptr_error();
    #endif
    return *ptr_left;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::right ( )
{
    #if debug
        if ( not has_right() )
            throw nullptr_error();
    #endif
    return *ptr_right;
}

template < class type >
constexpr const binary_tree<type>::node& binary_tree<type>::node::right ( ) const
{
    #if debug
        if ( not has_right() )
            throw nullptr_error();
    #endif
    return *ptr_right;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::another ( )
{
    #if debug
        if ( not has_another() )
            throw nullptr_error();
    #endif
    return is_left() ? up().right() otherwise
                       up().left ();
}

template < class type >
constexpr const binary_tree<type>::node& binary_tree<type>::node::another ( ) const
{
    #if debug
        if ( not has_another() )
            throw nullptr_error();
    #endif
    return is_left() ? up().right() otherwise
                       up().left ();
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::leftmost ( )
{
    node* ptr = this;
    while ( ptr -> has_left() )
        ptr = ptr -> ptr_left;

    return *ptr;
}

template < class type >
constexpr const binary_tree<type>::node& binary_tree<type>::node::leftmost ( ) const
{
    const node* ptr = this;
    while ( ptr -> has_left() )
        ptr = ptr -> ptr_left;

    return *ptr;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::rightmost ( )
{
    node* ptr = this;
    while ( ptr -> has_right() )
        ptr = ptr -> ptr_right;

    return *ptr;
}

template < class type >
constexpr const binary_tree<type>::node& binary_tree<type>::node::rightmost ( ) const
{
    const node* ptr = this;
    while ( ptr -> has_right() )
        ptr = ptr -> ptr_right;

    return *ptr;
}



template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::cut_up ( )
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif

    ( is_left() ? up().ptr_left otherwise up().ptr_right ) = nullptr;

    node* ptr = ptr_up;
    ptr_up = nullptr;

    return *ptr;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::cut_left ( )
{
    #if debug
        if ( not has_left() )
            throw nullptr_error();
    #endif

    left().ptr_up = nullptr;

    node* ptr = ptr_left;
    ptr_left = nullptr;

    return *ptr;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::cut_right ( )
{
    #if debug
        if ( not has_right() )
            throw nullptr_error();
    #endif

    right().ptr_up = nullptr;

    node* ptr = ptr_right;
    ptr_right = nullptr;

    return *ptr;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::link_left ( node& link )
{
    #if debug
        if ( has_left() or link.has_up() )
            throw nullptr_error();
    #endif

    self.ptr_left = &link;
    link.ptr_up   = &self;

    return *ptr_left;
}

template < class type >
constexpr binary_tree<type>::node& binary_tree<type>::node::link_right ( node& link )
{
    #if debug
        if ( has_right() or link.has_up() )
            throw nullptr_error();
    #endif

    self.ptr_right = &link;
    link.ptr_up    = &self;

    return *ptr_right;
}

template < class type >
constexpr void binary_tree<type>::node::delete_self ( )
{
    #if debug
        if ( has_up() )
            throw nullptr_error(); // Not been cut before
    #endif

    delete &self;
}

template < class type >
constexpr void binary_tree<type>::node::root_swap ( node& other )
{
    node* self_left   = self .has_left () ? &self .cut_left () otherwise nullptr;
    node* self_right  = self .has_right() ? &self .cut_right() otherwise nullptr;
    node* other_left  = other.has_left () ? &other.cut_left () otherwise nullptr;
    node* other_right = other.has_right() ? &other.cut_right() otherwise nullptr;

    if ( self_left != nullptr )
        other.link_left ( *self_left );
    if ( self_right != nullptr )
        other.link_right ( *self_right );

    if ( other_left != nullptr )
        self.link_left ( *other_left );
    if ( other_right != nullptr )
        self.link_right ( *other_right );
}



template < class type >
constexpr bool binary_tree<type>::node::has_up ( ) const
{
    return ptr_up != nullptr;
}

template < class type >
constexpr bool binary_tree<type>::node::has_left ( ) const
{
    return ptr_left != nullptr;
}

template < class type >
constexpr bool binary_tree<type>::node::has_right ( ) const
{
    return ptr_right != nullptr;
}

template < class type >
constexpr bool binary_tree<type>::node::has_another ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return is_left() ? up().has_right() otherwise
                       up().has_left ();
}

template < class type >
constexpr bool binary_tree<type>::node::is_left ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return up().ptr_left == &self;
}

template < class type >
constexpr bool binary_tree<type>::node::is_right ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return up().ptr_right == &self;
}

template < class type >
constexpr bool binary_tree<type>::node::is_leaf ( ) const
{
    return not has_left() and not has_right();
}

// Tree

template < class type >
constexpr pair<typename binary_tree<type>::node&,typename binary_tree<type>::node&> binary_tree<type>::node::copy_tree ( const node& from )
{
    #if debug
        if ( not is_leaf() )
            throw value_error();
    #endif

    return pair<node&,node&> ( from.has_left()  ? self.link_left  ( *new node ( from.left() .data, nullptr, nullptr, nullptr, from.left() .flag ) )
                                                      .copy_tree  ( from.left() )
                                                      .left() otherwise
                                                  self,
                               from.has_right() ? self.link_right ( *new node ( from.right().data, nullptr, nullptr, nullptr, from.right().flag ) )
                                                      .copy_tree  ( from.right() )
                                                      .right() otherwise
                                                  self
                             );
}

template < class type >
constexpr std::ostream& binary_tree<type>::node::print_tree ( std::ostream& str, int indent ) const
{
    for ( int _ in range ( indent ) )
        str << "  ";
    str << static_cast<const type&>(self) << '[' << flag << ']' << '\n';

    if ( is_leaf() )
        return str;

    if ( has_left() )
        self.left().print_tree ( str, indent + 1 );
    else
    {
        for ( int _ in range ( indent + 1 ) )
            str << "  ";
        str << '-' << '\n';
    }

    if ( has_right() )
        self.right().print_tree ( str, indent + 1 );
    else
    {
        for ( int _ in range ( indent + 1 ) )
            str << "  ";
        str << '-' << '\n';
    }

    return str;
}



/// Class binary_tree::const_iterator

// Conversion

template < class type >
constexpr binary_tree<type>::const_iterator::const_iterator ( const node* init )
    extends ptr ( init )
{

}

template < class type >
constexpr binary_tree<type>::const_iterator::operator const node* ( ) const
{
    return ptr;
}

// Interface

template < class type >
constexpr const type& binary_tree<type>::const_iterator::operator * ( ) const
{
    return static_cast<const type&>(*ptr);
}

template < class type >
constexpr const type* binary_tree<type>::const_iterator::operator -> ( ) const
{
    return &static_cast<const type&>(*ptr);
}

template < class type >
constexpr binary_tree<type>::const_iterator& binary_tree<type>::const_iterator::operator ++ ( )
{
    if ( (*ptr).has_right() )
        ptr = &(*ptr).right().leftmost();
    else
        if ( (*ptr).is_left() )
            ptr = &(*ptr).up();
        else
        {
            while ( not (*ptr).is_left() )
                ptr = &(*ptr).up();
            ptr = &(*ptr).up();
        }

    return self;
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::const_iterator::operator ++ ( int )
{
    let it = self;
    ++self;
    return it;
}

template < class type >
constexpr binary_tree<type>::const_iterator& binary_tree<type>::const_iterator::operator -- ( )
{
    if ( (*ptr).has_left() )
        ptr = &(*ptr).left().rightmost();
    else
        if ( (*ptr).is_right() )
            ptr = &(*ptr).up();
        else
        {
            while ( not (*ptr).is_right() )
            {
                ptr = &(*ptr).up();

                if ( not (*ptr).has_up() ) // Pointing to root.
                    return self;
            }
            ptr = &(*ptr).up();
        }

    return self;
}

template < class type >
constexpr binary_tree<type>::const_iterator binary_tree<type>::const_iterator::operator -- ( int )
{
    let it = self;
    --self;
    return it;
}



/// Global

template < class type >
std::ostream& operator << ( std::ostream& left, const binary_tree<type>& right )
    requires printable<type>
{
    return right.print_tree(left);
}





















