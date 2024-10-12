#pragma once

/* Note:
 * Binary_tree ( with trees based on binary_tree ) provides and only provides interfaces below:
 *
 * constructor, destructor, copy, move.
 * begin(), end(), min(), mid(), max(), locate(). [[ locate()      is always shortest  ]].
 * clear(), erase(), push(), pop().               [[ push(), pop() is always rightmost ]].
 *
 * In default compare mode, no repeated items are allowed.
 */

template < class type >
class binary_tree
{
    protected: // Class
        class node;

    private: // Data
        int         m       = 0;
        node        root    = node(); // root always not has_right() and link its left to data.
        const node* ptr_min = nullptr;
        const node* ptr_max = nullptr;

    public: // Typedef
        using value_type = type;
        class const_iterator;

    public: // Core
        constexpr  binary_tree ( ) = default;
        constexpr  binary_tree ( const binary_tree&  );
        constexpr  binary_tree (       binary_tree&& );
        constexpr  binary_tree& operator = ( binary_tree );

    public: // Interface
        constexpr  int            size    ( )     const;
        constexpr  bool           empty   ( )     const;

        constexpr  const_iterator begin   ( )     const;
        constexpr  const_iterator end     ( )     const;
        constexpr  const_iterator min     ( )     const;
        constexpr  const_iterator mid     ( )     const;
        constexpr  const_iterator max     ( )     const;
        constexpr  const_iterator clear   ( );

    public: // Print
        std::ostream& print_tree ( std::ostream& ) const;

    protected: // Auxiliary
        constexpr int&         get_size    ( );
        constexpr const node*& get_min     ( );
        constexpr const node*& get_max     ( );
};




template < class type >
class binary_tree<type>::node
{
    private: // Data
        type  data      = type();
        node* ptr_up    = nullptr;
        node* ptr_left  = nullptr;
        node* ptr_right = nullptr;
        int   flag      = 0;

    public: // Typedef
        using value_type = type;

    public: // Core
        constexpr  node ( )              = default;
        constexpr  node ( const node&  ) = delete;
        constexpr  node (       node&& ) = delete;
        constexpr  node ( std::convertible_to<type> auto&& );
        constexpr  node ( std::convertible_to<type> auto&&, node*, node*, node*, int = 0 );
        constexpr ~node ( );

    public: // Conversion
        constexpr operator       type& ( );
        constexpr operator const type& ( ) const;
        constexpr       int&     info  ( );
        constexpr const int&     info  ( ) const;

    public: // Interface
        constexpr       node& up          ( );
        constexpr const node& up          ( ) const;
        constexpr       node& left        ( );
        constexpr const node& left        ( ) const;
        constexpr       node& right       ( );
        constexpr const node& right       ( ) const;
        constexpr       node& another     ( );
        constexpr const node& another     ( ) const;
        constexpr       node& leftmost    ( );
        constexpr const node& leftmost    ( ) const;
        constexpr       node& rightmost   ( );
        constexpr const node& rightmost   ( ) const;

        constexpr       node& cut_up      ( );
        constexpr       node& cut_left    ( );
        constexpr       node& cut_right   ( );
        constexpr       node& link_left   ( node& );
        constexpr       node& link_right  ( node& );
        constexpr       void  delete_self ( );
        constexpr       void  root_swap   ( node& );

        constexpr       bool  has_up      ( ) const;
        constexpr       bool  has_left    ( ) const;
        constexpr       bool  has_right   ( ) const;
        constexpr       bool  has_another ( ) const;
        constexpr       bool  is_left     ( ) const;
        constexpr       bool  is_right    ( ) const;
        constexpr       bool  is_leaf     ( ) const;

    public: // Tree
        constexpr pair<node&,node&> copy_tree  ( const node& );
        constexpr std::ostream&     print_tree ( std::ostream&, int = 0 ) const;
};




template < class type >
class binary_tree<type>::const_iterator
{
    private: // Data
        const node* ptr = nullptr;

    public: // Typedef
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const type*;
        using reference         = const type&;

    public: // Core
        constexpr const_iterator ( ) = default;

    public: // Conversion
        constexpr const_iterator ( const node* );
        constexpr operator         const node* ( ) const;

    public: // Interface
        constexpr const type&     operator  * ( )                       const;
        constexpr const type*     operator -> ( )                       const;
        constexpr bool            operator == ( const const_iterator& ) const = default;
        constexpr bool            operator != ( const const_iterator& ) const = default;
        constexpr const_iterator& operator ++ ( );
        constexpr const_iterator  operator ++ ( int );
        constexpr const_iterator& operator -- ( );
        constexpr const_iterator  operator -- ( int );
};



template < class type > std::ostream& operator << ( std::ostream&, const binary_tree<type>& ) requires printable<type>;


#include "binary_tree.cpp"

