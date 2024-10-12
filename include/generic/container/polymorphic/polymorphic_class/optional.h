#pragma once

/// Declaration

class nullopt_t { };
constexpr nullopt_t nullopt = nullopt_t();




template < class types >
class optional
{
    private: // Precondition
        static_assert ( not is_const<types> and not is_volatile<types> and not is_reference<types> );
        static_assert ( std::default_initializable<types> and std::movable<types> );

    private: // Base
        union union_obj;

    private: // Data
        union_obj data;
        bool      flag = false;

    public: // Typedef
        using value_type = types;

    public: // Core
        constexpr  optional ( );
        constexpr  optional ( const optional&  )             requires std::copyable<types>;
        constexpr  optional (       optional&& );
        constexpr  optional ( types );
        constexpr  optional ( nullopt_t );
        constexpr ~optional ( );
        constexpr  optional& operator = ( const optional&  ) requires std::copyable<types>;
        constexpr  optional& operator = (       optional&& );
        constexpr  optional& operator = ( types );
        constexpr  optional& operator = ( nullopt_t );

    public: // Conversion
        constexpr explicit operator       types& ( );
        constexpr explicit operator const types& ( ) const;

    public: // Member
        constexpr bool type ( ) const;
};

#include "optional.cpp"
