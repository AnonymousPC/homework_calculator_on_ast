#pragma once

constexpr array_type auto fft ( const array_type auto& vector )
    requires ( vector.dimension() == 1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> )
{
    if constexpr ( int_type<vector_value_type> or complex_int_type<vector_value_type> )
        return fft ( vector.template as_type<int_to_float_type<vector_value_type>>() );
    else if constexpr ( float_type<vector_value_type> or complex_float_type<vector_value_type> )
    {
        #if debug
            int t = 1;
            while ( t < vector.size() )
                t *= 2;
            if ( t != vector.size() )
                throw value_error("cannot fft vector of size {}: size must be 2^n", vector.size());
        #endif

        try
        {
            if constexpr ( float_type<vector_value_type> )
            {
                let a = aux::to_eigen(vector);
                let b = Eigen::Vector<std::complex<vector_value_type>,Eigen::Dynamic>(a.size());
                Eigen::FFT<vector_value_type>().fwd(b, a);
                return aux::from_eigen(b);
            }
            else if constexpr ( complex_float_type<vector_value_type> )
            {
                let a = aux::to_eigen(vector);
                let b = Eigen::Vector<std::complex<vector_value_type::value_type>,Eigen::Dynamic>(a.size());
                Eigen::FFT<vector_value_type::value_type>().fwd(b, a);
                return aux::from_eigen(b);
            }
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot fft vector: [[from {}]] {}", "eigen", e.what());
        }
    }
}

constexpr array_type auto ifft ( const array_type auto& vector )
    requires ( vector.dimension() == 1 ) and ( number_type<vector_value_type> or complex_type<vector_value_type> )
{
    if constexpr ( int_type<vector_value_type> )
        return ifft ( vector.template as_type<complex<int_to_float_type<vector_value_type>>>() );
    else if constexpr ( float_type<vector_value_type> )
        return ifft ( vector.template as_type<complex<vector_value_type>>() );
    else if constexpr ( complex_int_type<vector_value_type> )
        return ifft ( vector.template as_type<int_to_float_type<vector_value_type>>() );
    else if constexpr ( complex_float_type<vector_value_type> )
    {
        #if debug
            int t = 1;
            while ( t < vector.size() )
                t *= 2;
            if ( t != vector.size() )
                throw value_error("cannot ifft vector of size {}: size must be 2^n", vector.size());
        #endif

        try
        {
            let a = aux::to_eigen(vector);
            let b = Eigen::Vector<std::complex<vector_value_type::value_type>,Eigen::Dynamic>(a.size());
            Eigen::FFT<vector_value_type::value_type>().inv(b, a);
            return aux::from_eigen(b);
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot ifft vector: [[from {}]] {}", "eigen", e.what());
        }
    }
}
