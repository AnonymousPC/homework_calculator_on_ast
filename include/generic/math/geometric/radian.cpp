#pragma once

/// Class radian

template < float_type type >
class radian
{
    private: // Data
        type t = 0;

    public: // Typedef
        using value_type = type;
        struct angle_tag  { };
        struct radian_tag { };

    public: // Core
        constexpr radian ( ) = default;
        constexpr radian ( type );
        constexpr const type& value ( ) const;

    public: // Conversion
        constexpr radian ( degree_type auto );
        constexpr radian ( radian_type auto );

    public: // Operator
        constexpr bool operator ==  ( const radian& ) const = default;
        constexpr auto operator <=> ( const radian& ) const = default;
};

template < int_type   type > radian ( type )         -> radian<>;
template < float_type type > radian ( type )         -> radian<type>;
template < float_type type > radian ( degree<type> ) -> radian<type>;

// Core

template < float_type type >
constexpr radian<type>::radian ( type init )
    extends t ( init )
{

}

template < float_type type >
constexpr const type& radian<type>::value ( ) const
{
    return t;
}

// Conversion

template < float_type type >
constexpr radian<type>::radian ( degree_type auto cvt )
    extends radian ( static_cast<type> ( cvt.value() ) * ( 2 * constants::pi ) / 360 )
{

}

template < float_type type >
constexpr radian<type>::radian ( radian_type auto cvt )
    extends radian ( static_cast<type> ( cvt.value() ) )
{

}



/// Global

template < float_type type >
std::ostream& operator << ( std::ostream& left, const radian<type>& right )
{
    return left << right.value() << "rad";
}

template < float_type type >
constexpr radian<type> operator + ( const radian<type>& right )
{
    return right;
}

template < float_type type >
constexpr radian<type> operator - ( const radian<type>& right )
{
    return radian<type> ( - right.value() );
}

template < float_type type >
constexpr radian<type> operator + ( const radian<type>& left, const radian<type>& right )
{
    return radian<type> ( left.value() + right.value() );
}

template < float_type type >
constexpr radian<type> operator - ( const radian<type>& left, const radian<type>& right )
{
    return radian<type> ( left.value() - right.value() );
}

template < float_type type >
constexpr radian_type auto /* as right is auto */ operator * ( const radian<type>& left, const number_type auto& right ) // Does not pass std::common_type.
{
    return radian ( left.value() * right );
}

template < float_type type >
constexpr radian_type auto /* as right is auto */ operator * ( const number_type auto& left, const radian<type>& right ) // Does not pass std::common_type.
{
    return radian ( left * right.value() );
}

template < float_type type >
constexpr float_type auto /* as result is number */ operator / ( const radian<type>& left, const radian<type>& right )
{
    if ( right.value() == 0 )
        throw math_error("{} / {}", left, right);

    return left.value() / right.value();
}

template < float_type type >
constexpr radian_type auto /* as right is auto */ operator / ( const radian<type>& left, const number_type auto& right ) // Does not pass std::common_type.
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    return radian ( left.value() / right );
}






