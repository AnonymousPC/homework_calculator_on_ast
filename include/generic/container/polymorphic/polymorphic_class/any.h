#pragma once

class any
{
    private: // Base
                                 class static_obj;
        template < class types > class dynamic_obj;

    private: // Data
        static_obj*           ptr  = nullptr;
        const std::type_info* rtti = nullptr;

    public: // Core
        constexpr  any ( )                    = default;
        constexpr  any ( const any&  );
        constexpr  any (       any&& );
        constexpr  any ( std::copyable auto );
        constexpr ~any ( );
        constexpr  any& operator = ( const any&  );
        constexpr  any& operator = (       any&& );

    public: // Conversion
        template < class types > constexpr operator       types& ( )       requires ( not is_const<types> );
        template < class types > constexpr operator const types& ( ) const;

    public: // Member
        constexpr const std::type_info& type ( ) const;
};

#include "any.cpp"
