#pragma once

/// Class basic_map

// Core

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::basic_map ( std::initializer_list<pair<type1,type2>>&& init )
{
    for ( const pair<type1,type2>& p in init )
    {
        let it = data.locate(p.key());

        if ( empty() or it->key() != p.key() )
            data.push ( std::move ( const_cast<pair<type1,type2>&>(p) ), it );

        #if debug
            else if constexpr ( equalable<type2> ) // it->key() == p.key().
                if ( not empty() and it->value() != p.value() )
                    throw key_error("key {} with conflicing values {} and {}", p.key(), p.value(), it->value());
        #endif
    }
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::basic_map ( std::from_range_t, std::ranges::input_range auto&& init )
    requires requires { std::declval<basic_map>()[get<0>(*init.begin())] = get<1>(*init.begin()); }
{
    for ( auto&& p in init )
        self[std::move(get<0>(p))] = std::move(get<1>(p));
}




// Conveesion

template < class type1, class type2, class key_less, class container >
constexpr auto& basic_map<type1,type2,key_less,container>::data_handle ( )
{
    if constexpr ( requires { data.data_handle(); } )
        return data.data_handle();
    else
        return data;
}

template < class type1, class type2, class key_less, class container >
constexpr const auto& basic_map<type1,type2,key_less,container>::data_handle ( ) const
{
    if constexpr ( requires { data.data_handle(); } )
        return data.data_handle();
    else
        return data;
}


// Interface

template < class type1, class type2, class key_less, class container >
constexpr int basic_map<type1,type2,key_less,container>::size ( ) const
{
    return data.size();
}

template < class type1, class type2, class key_less, class container >
constexpr bool basic_map<type1,type2,key_less,container>::empty ( ) const
{
    return size() == 0;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::begin ( )
{
    return iterator ( data.begin() );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::begin ( ) const
{
    return const_iterator ( data.begin() );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::end ( )
{
    return iterator ( data.end() );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::end ( ) const
{
    return const_iterator ( data.end() );
}

template < class type1, class type2, class key_less, class container >
constexpr type2& basic_map<type1,type2,key_less,container>::operator [] ( type1&& k )
{
    let it = data.locate(k);

    if ( empty() or it->key() != k )
        it = data.push ( pair<type1&&,type2&&> ( std::move(k), type2() ), it );

    return const_cast<type2&> ( it->value() );
}

template < class type1, class type2, class key_less, class container >
constexpr type2& basic_map<type1,type2,key_less,container>::operator [] ( const type1& k )
{
    let it = data.locate(k);

    if ( empty() or it->key() != k )
        it = data.push ( pair<const type1&,type2&&> ( k, type2() ), it );

    return const_cast<type2&> ( it->value() );
}

template < class type1, class type2, class key_less, class container >
constexpr const type2& basic_map<type1,type2,key_less,container>::operator [] ( const type1& k ) const
{
    let it = data.locate(k);

    if ( empty() or it->key() != k )
        #if debug
            throw index_error("key {} does not exist", k);
        #else
            return end()->value(); // Undefined behaviour, which matches the behaviour of index_error.
        #endif                     // Imaging you are operating an std::vector with invalid index, the result
                                   // might be segfault, invalid_but_no_segfault(e.x. out of size but in capacity), ...
    return it->value();            // No matter which case happens, it must satisfy the following 2 predicts:
}                                  // 1.Nobody can predict what happens. 2.It acts in same way as *end().

template < class type1, class type2, class key_less, class container >
constexpr const auto basic_map<type1,type2,key_less,container>::keys ( ) const
{
    return collection_keys_view ( const_cast<basic_map&>(self) );
}

template < class type1, class type2, class key_less, class container >
constexpr auto basic_map<type1,type2,key_less,container>::values ( )
{
    return collection_values_view ( self );
}

template < class type1, class type2, class key_less, class container >
constexpr const auto basic_map<type1,type2,key_less,container>::values ( ) const
{
    return collection_values_view ( const_cast<basic_map&>(self) );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>& basic_map<type1,type2,key_less,container>::clear ( )
{
    data.clear();
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr bool basic_map<type1,type2,key_less,container>::contains ( const type1& k ) const
{
    return not empty() and data.locate(k)->key() == k;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>& basic_map<type1,type2,key_less,container>::pop ( const type1& k )
{
    let it = data.locate(k);

    #if debug
        if ( empty() or it->key() != k )
            throw key_error("key {} does not exist", k);
    #endif

    data.pop ( k, it );

    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>& basic_map<type1,type2,key_less,container>::update ( const map_type<type1,type2> auto& upd )
{
    for ( const auto& [k,v] in upd )
        self[k] = upd[k];

    return self;
}



/// Class basic_map::iterator

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator::iterator ( const container::const_iterator& init )
    extends data ( init )
{

}

template < class type1, class type2, class key_less, class container >
constexpr pair<const type1,type2>& basic_map<type1,type2,key_less,container>::iterator::operator * ( ) const
{
    return const_cast<pair<const type1,type2>&> ( static_cast<const pair<const type1,type2>&> ( *data ) );
}

template < class type1, class type2, class key_less, class container >
constexpr pair<const type1,type2>* basic_map<type1,type2,key_less,container>::iterator::operator -> ( ) const
{
    return &operator*();
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator& basic_map<type1,type2,key_less,container>::iterator::operator ++ ( )
{
    ++data;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator ++ ( int )
{
    let it = self;
    ++self;
    return it;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator& basic_map<type1,type2,key_less,container>::iterator::operator -- ( )
{
    --data;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator -- ( int )
{
    let it = self;
    --self;
    return it;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator + ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return data + offset;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator - ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return data - offset;
}

template < class type1, class type2, class key_less, class container >
constexpr int basic_map<type1,type2,key_less,container>::iterator::operator - ( const iterator& right ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return data - right.data;
}

/// Class basic_map::const_iterator

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator::const_iterator ( const container::const_iterator& init )
    extends data ( init )
{

}

template < class type1, class type2, class key_less, class container >
constexpr const pair<const type1,type2>& basic_map<type1,type2,key_less,container>::const_iterator::operator * ( ) const
{
    return static_cast<const pair<const type1,type2>&> ( *data );
}

template < class type1, class type2, class key_less, class container >
constexpr const pair<const type1,type2>* basic_map<type1,type2,key_less,container>::const_iterator::operator -> ( ) const
{
    return &operator*();
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator& basic_map<type1,type2,key_less,container>::const_iterator::operator ++ ( )
{
    ++data;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator ++ ( int )
{
    let it = self;
    ++self;
    return it;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator& basic_map<type1,type2,key_less,container>::const_iterator::operator -- ( )
{
    --data;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator -- ( int )
{
    let it = self;
    --self;
    return it;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator + ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return data + offset;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator - ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return data - offset;
}

template < class type1, class type2, class key_less, class container >
constexpr int basic_map<type1,type2,key_less,container>::const_iterator::operator - ( const const_iterator& right ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return data - right.data;
}


