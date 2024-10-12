#pragma once


/// Class array

// Core

template < class type >
constexpr array<type>::array ( const array& init )
    requires std::copyable<type>
    extends m    ( init.m ),
            data ( allocate ( size() ) )
{
    std::copy ( init.begin(), init.end(), begin() );
}

template < class type >
constexpr array<type>::array ( array&& init )
    extends m    ( std::exchange ( init.m,    0       ) ),
            data ( std::exchange ( init.data, nullptr ) )
{

}

template < class type >
constexpr array<type>::array ( int init_size )
    extends m    ( init_size ),
            data ( allocate ( size() ) )
{
    #if debug
        if ( size() < 0 )
            throw value_error("initialize array with negative size {}", size());
    #endif
}

template < class type >
constexpr array<type>::array ( int init_size, const type& init_data )
    requires std::copyable<type>
    extends array ( init_size )
{
    std::fill ( begin(), end(), init_data );
}

template < class type >
constexpr array<type>::array ( int init_size, function_type<type()> auto init_data )
    extends array ( init_size )
{
    std::generate ( begin(), end(), init_data );
}

template < class type >
constexpr array<type>::array ( int init_size, function_type<type(int)> auto init_data )
    extends array ( init_size )
{
    for ( int i in range ( size() ) )
        self[i] = init_data(i);
}

template < class type >
constexpr array<type>::array ( std::initializer_list<type>&& init )
    extends array ( init.size() )
{
    std::move ( const_cast<type*>(init.begin()), const_cast<type*>(init.end()), self.begin() );
}

template < class type >
constexpr array<type>::array ( const array_type<type,1> auto& init )
    requires std::copyable<type>
    extends array ( init.size() )
{
    std::copy ( init.begin(), init.end(), begin() );
}

template < class type >
constexpr array<type>::array ( const array_type auto& init )
    requires ( not std::same_as<typename decay<decltype(init)>::value_type,type> ) but
             std::convertible_to<typename decay<decltype(init)>::value_type,type> and
             ( decay<decltype(init)>::dimension() == 1 )
    extends array ( init.size() )
{
    std::transform ( init.begin(), init.end(), begin(), [] (const auto& item) { return type(item); } );
}

template < class type >
constexpr array<type>::array ( const range_type<type> auto& init )
    requires std::copyable<type>
    extends array ( init.size() )
{
    std::copy ( init.begin(), init.end(), begin() );
}

template < class type >
constexpr array<type>::array ( const range_type auto& init )
    requires ( not std::same_as<typename decay<decltype(init)>::value_type,type> ) but
             std::convertible_to<typename decay<decltype(init)>::value_type,type>
    extends array ( init.size() )
{
    std::transform ( init.begin(), init.end(), begin(), [] (const auto& item) { return type(item); } );
}

template < class type >
constexpr array<type>::array ( std::from_range_t, std::ranges::input_range auto&& init )
    requires requires { std::declval<array>().push(*init.begin()); }
{
    if constexpr ( requires { init.size(); self[1] = *init.begin(); } )
    {
        resize ( init.size() );
        std::move ( init.begin(), init.end(), begin() );
    }

    else
        for ( auto&& item in init )
            self.push(item);
}

template < class type >
constexpr array<type>::array ( std::from_range_t, std::ranges::input_range auto&& init, int init_size )
    requires ( requires { std::declval<array>().push(*init.begin()); } )
    extends array ( init_size )
{
    int i = 0;
    for ( auto&& item in init )
    {
        i++;

        #if debug
            if ( i > size() )
                throw value_error("cannot move range of size >= {} into array of size {}", i, size());
        #endif
        self[i] = std::move(item);
    }

    #if debug
        if ( i < size() )
            throw value_error("cannot move range of size {} into array of size {}", i, size());
    #endif
}

template < class type >
constexpr array<type>::~array ( )
{
    deallocate ( data );
}

template < class type >
constexpr array<type>& array<type>::operator = ( const array& right )
    requires std::copyable<type>
{
    resize ( right.size() );
    std::copy ( right.begin(), right.end(), begin() );
    return self;
}

template < class type >
constexpr array<type>& array<type>::operator = ( array&& right )
{
    std::swap ( self.m,    right.m    );
    std::swap ( self.data, right.data );
    return self;
}

// Conversion

template < class type >
template < class type2 >
constexpr array<type>::array ( const array<type2>& cvt )
    requires std::convertible_to<type2,type> but ( not std::same_as<type,type2> )
    extends array ( cvt.size() )
{
    std::transform ( cvt.begin(), cvt.end(), begin(), [] ( const type2& val ) { return type(val); } );
}

template < class type >
template < class type2 >
constexpr array<type>::array ( const array<type2>& cvt )
    requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    std::transform ( cvt.begin(), cvt.end(), begin(), [] ( const type2& val ) { return type(val); } );
}

// Interface

template < class type >
constexpr int array<type>::size ( ) const
{
    return m;
}

template < class type >
constexpr bool array<type>::empty ( ) const
{
    return size() == 0;
}

template < class type >
constexpr array<type>& array<type>::resize ( int new_size )
{
    #if debug
        if ( new_size < 0 )
            throw value_error("cannot resize array of size {} into size {}", size(), new_size);
    #endif

    if ( capacity(size()) != capacity(new_size) ) // Needs new allocation.
    {
        array tmp = array ( new_size );

        std::move ( begin(), begin() + std::min ( size(), tmp.size() ), tmp.begin() );
        std::swap ( self.m,    tmp.m    );
        std::swap ( self.data, tmp.data );
    }

    else // Reuse allocated memory.
    {
        if ( new_size < size() )
            std::fill ( begin() + new_size, begin() + size(), type() );

        m = new_size;
    }

    return self;
}

template < class type >
constexpr array<type>::iterator array<type>::begin ( )
{
    return data;
}

template < class type >
constexpr array<type>::const_iterator array<type>::begin ( ) const
{
    return data;
}

template < class type >
constexpr array<type>::iterator array<type>::end ( )
{
    return data + size();
}

template < class type >
constexpr array<type>::const_iterator array<type>::end ( ) const
{
    return data + size();
}

template < class type >
constexpr type& array<type>::operator [] ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? data[pos-1] otherwise data[pos+size()];
}

template < class type >
constexpr const type& array<type>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? data[pos-1] otherwise data[pos+size()];
}

// Auxiliary

template < class type >
constexpr type* array<type>::allocate ( int len )
{
    #if debug
        if ( len < 0 )
            throw value_error();
    #endif

    return len == 0 ? nullptr otherwise new type[capacity(len)+1] {}; // Allocate one more byte to make gcc happy.
}

template < class type >
constexpr void array<type>::deallocate ( type* addr )
{
    return delete[] addr;
}

template < class type >
constexpr int array<type>::capacity ( int len )
{
    if ( len == 0 )
        return 0;

    int cap = 1;
    while ( cap < len )
        cap *= 2;

    return cap;
}





