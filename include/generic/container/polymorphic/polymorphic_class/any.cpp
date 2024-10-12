#pragma once

/** As class any is not template, it requires a correct
  * declaration and depend sequence, which desires
  * class any::static_obj and any::dynamic_obj to be
  * defined before any is implemented.
  */

/// Class any::dynamic_obj

// Declaration

class any::static_obj
{
    public: // Core
        virtual constexpr ~static_obj       ( )       = default;
        virtual constexpr  static_obj& copy ( ) const = abstract;
};

template < class types >
class any::dynamic_obj
    extends public static_obj
{
    public: // Data
        types data;

    public: // Core
        constexpr  dynamic_obj      ( types );
        constexpr ~dynamic_obj      ( )       override = default;
        constexpr  static_obj& copy ( ) const override;
};


// Implemention

template < class types >
constexpr any::dynamic_obj<types>::dynamic_obj ( types init )
    extends data ( std::move ( init ) )
{

}

template < class types >
constexpr any::static_obj& any::dynamic_obj<types>::copy ( ) const
{
    return *new dynamic_obj ( self );
}






/// Class any

// Core

constexpr any::any ( const any& init )
    extends ptr  ( init.ptr != nullptr ? &init.ptr->copy() otherwise nullptr ),
            rtti ( init.rtti )
{

}

constexpr any::any ( any&& init )
    extends ptr  ( std::exchange ( init.ptr,  nullptr ) ),
            rtti ( std::exchange ( init.rtti, nullptr ) )
{

}

constexpr any::any ( std::copyable auto init )
    extends ptr  ( new dynamic_obj ( std::move ( init ) ) ),
            rtti ( &typeid ( init ) )
{

}

constexpr any::~any ( )
{
    delete ptr;
}

constexpr any& any::operator = ( const any& right )
{
    delete ptr;

    ptr  = right.ptr != nullptr ? &right.ptr->copy() otherwise nullptr;
    rtti = right.rtti;

    return self;
}

constexpr any& any::operator = ( any&& right )
{
    std::swap ( ptr,  right.ptr  );
    std::swap ( rtti, right.rtti );

    return self;
}

// Conversion

template < class types >
constexpr any::operator types& ( )
    requires ( not is_const<types> )
{
    let p = dynamic_cast<dynamic_obj<types>*> ( ptr );

    if ( p != nullptr )
        return p->data;
    else
        throw type_error("bad any access: cannot get {} from {}, whose type == {}",
                         typeid(types&), typeid(self), self.type());
}

template < class types >
constexpr any::operator const types& ( ) const
{
    let p = dynamic_cast<dynamic_obj<types>*> ( ptr );

    if ( p != nullptr )
        return p->data;
    else
        throw type_error("bad any access: cannot get {} from {}, whose type == {}",
                         typeid(const types&), typeid(self), self.type());
}

// Member

constexpr const std::type_info& any::type ( ) const
{
    return rtti == nullptr ? typeid(void) otherwise *rtti;
}




