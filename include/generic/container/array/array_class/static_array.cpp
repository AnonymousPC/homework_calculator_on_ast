#pragma once

/// Class static_array

// Interface

template < class type, int len >
constexpr int static_array<type,len>::size ( )
{
    return len;
}

template < class type, int len >
constexpr bool static_array<type,len>::empty ( )
{
    return size() == 0;
}

template < class type, int len >
constexpr static_array<type,len>::iterator static_array<type,len>::begin ( )
{
    return self.data;
}

template < class type, int len >
constexpr static_array<type,len>::const_iterator static_array<type,len>::begin ( ) const
{
    return self.data;
}

template < class type, int len >
constexpr static_array<type,len>::iterator static_array<type,len>::end ( )
{
    return self.data + size();
}

template < class type, int len >
constexpr static_array<type,len>::const_iterator static_array<type,len>::end ( ) const
{
    return self.data + size();
}

template < class type, int len >
constexpr type& static_array<type,len>::operator [] ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? self.data[pos-1] otherwise self.data[pos+size()];
}

template < class type, int len >
constexpr const type& static_array<type,len>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? self.data[pos-1] otherwise self.data[pos+size()];
}















/// Auxiliary

template < class type, int len >
struct aux::static_array_base
{
    type data[len] = {};
};





