#pragma once

/// Class complex

template < number_type type >
class complex
{
    private: // Data
        type x = 0;
        type y = 0;

    public: // Typedef
        using value_type = type;
        struct complex_tag { };

    public: // Core
        constexpr complex ( ) = default;
        constexpr complex ( type );
        constexpr complex ( type, type );
        constexpr const type& real ( ) const;
        constexpr const type& imag ( ) const;

    public: // Conversion
        constexpr complex ( number_type  auto );
        constexpr complex ( complex_type auto );
        constexpr complex ( polar_type   auto p ) requires float_type<type> and float_type<typename decltype(p)::value_type>;

    public: // Operator
        constexpr bool operator == ( const complex& ) const = default;
        constexpr bool operator != ( const complex& ) const = default;
};

// Core

template < number_type type >
constexpr complex<type>::complex ( type init_x )
    extends x ( init_x )
{

}

template < number_type type >
constexpr complex<type>::complex ( type init_x, type init_y )
    extends x ( init_x ),
            y ( init_y )
{

}

template < number_type type >
constexpr const type& complex<type>::real ( ) const
{
    return x;
}

template < number_type type >
constexpr const type& complex<type>::imag ( ) const
{
    return y;
}

// Conversion

template < number_type type >
constexpr complex<type>::complex ( number_type auto cvt )
    extends complex ( static_cast<type> ( cvt ) )
{

}

template < number_type type >
constexpr complex<type>::complex ( complex_type auto cvt )
    extends complex ( static_cast<type> ( cvt.real() ), static_cast<type> ( cvt.imag() ) )
{

}

template < number_type type >
constexpr complex<type>::complex ( polar_type auto cvt )
    requires float_type<type> and float_type<typename decltype(cvt)::value_type>
    extends complex ( cvt.abs() * cos ( cvt.arg() ), cvt.abs() * sin ( cvt.arg() ) )
{

}





/// Global

template < number_type type >
std::ostream& operator << ( std::ostream& left, const complex<type>& right )
{
    if ( right.imag() == 0 )
        return left << right.real();
    else if ( right.imag() > 0 )
        return left << right.real() << '+' << right.imag() << 'i';
    else
        return left << right.real() << right.imag() << 'i';
}

template < number_type type >
constexpr complex<type> operator + ( const complex<type>& right )
{
    return right;
}

template < number_type type >
constexpr complex<type> operator - ( const complex<type>& right )
{
    return complex ( - right.real(), - right.imag() );
}

template < number_type type >
constexpr complex<type> operator + ( const complex<type>& left, const complex<type>& right )
{
    return complex ( left.real() + right.real(), left.imag() + right.imag() );
}

template < number_type type >
constexpr complex<type> operator - ( const complex<type>& left, const complex<type>& right )
{
    return complex ( left.real() - right.real(), left.imag() - right.imag() );
}

template < number_type type >
constexpr complex<type> operator * ( const complex<type>& left, const complex<type>& right )
{
    return complex ( left.real() * right.real() - left.imag() * right.imag(),
                     left.real() * right.imag() + left.imag() * right.real() );
}

template < number_type type >
constexpr complex<type> operator / ( const complex<type>& left, const complex<type>& right )
{
    type div = right.real() * right.real() + right.imag() * right.imag();

    if ( div == 0 )
        throw math_error("{} / {}", left, right);

    return complex ( ( left.real() * right.real() + left.imag() * right.imag() ) / div,
                     ( left.imag() * right.real() - left.real() * right.imag() ) / div );
}


