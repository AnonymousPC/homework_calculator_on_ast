#pragma once

/// Class basic_set

// Core

template < class type, class less, class container >
constexpr basic_set<type,less,container>::basic_set ( std::initializer_list<type>&& init )
{
    for ( const type& val in init )
        self.push ( std::move ( const_cast<type&> ( val ) ) );
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>::basic_set ( std::from_range_t, std::ranges::input_range auto&& init )
    requires requires { std::declval<basic_set>().push(*init.begin()); }
{
    for ( auto&& val in init )
        self.push ( std::move ( val ) );
}

// Conversion

template < class type, class less, class container >
constexpr auto& basic_set<type,less,container>::data_handle ( )
{
    if constexpr ( requires { data.data_handle(); } )
        return data.data_handle();
    else
        return data;
}

template < class type, class less, class container >
constexpr const auto& basic_set<type,less,container>::data_handle ( ) const
{
    if constexpr ( requires { data.data_handle(); } )
        return data.data_handle();
    else
        return data;
}

// Interface

template < class type, class less, class container >
constexpr int basic_set<type,less,container>::size ( ) const
{
    return data.size();
}

template < class type, class less, class container >
constexpr bool basic_set<type,less,container>::empty ( ) const
{
    return size() == 0;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>::const_iterator basic_set<type,less,container>::begin ( ) const
{
    return data.begin();
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>::const_iterator basic_set<type,less,container>::end ( ) const
{
    return data.end();
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::clear ( )
{
    data.clear();
    return self;
}

template < class type, class less, class container >
constexpr bool basic_set<type,less,container>::contains ( const type& val ) const
{
    return not empty() and *data.locate(val) == val;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::push ( type val )
{
    auto it = data.locate(val);
    if ( empty() or *it != val ) // Not contains.
        data.push ( std::move ( val ), it );

    return self;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::pop ( const type& val )
{
    auto it = data.locate(val);
    #if debug
        if ( empty() or *it != val )
            throw key_error("key {} does not exist", val);
    #endif
    data.pop ( val, it );

    return val;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::update ( const set_type<type> auto& upd )
{
    // TODO: Optimizable if less is same.

    for ( const auto& val in upd )
    {
        let it = data.locate(val);

        if ( empty() or *it != val ) // Update if not contains.
            data.push ( val, it );
    }
}



