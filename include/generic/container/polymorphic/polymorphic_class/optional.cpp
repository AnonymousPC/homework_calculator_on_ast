#pragma once

/// Class optional

// Core

template < class types >
constexpr optional<types>::optional ( )
{

}

template < class types >
constexpr optional<types>::optional ( const optional& init )
    requires std::copyable<types>
    extends data ( init.data, init.flag ),
            flag ( init.flag )
{

}

template < class types >
constexpr optional<types>::optional ( optional&& init )
    extends data ( std::move ( init.data ), init.flag ),
            flag ( std::exchange ( init.flag, false ) )
{

}

template < class types >
constexpr optional<types>::optional ( types init )
    extends data ( std::move ( init ) ),
            flag ( true )
{

}

template < class types >
constexpr optional<types>::optional ( nullopt_t )
    extends optional()
{

}

template < class types >
constexpr optional<types>::~optional ( )
{
    if ( flag )
    {
        data.clear();
        flag = false;
    }
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( const optional& right )
    requires std::copyable<types>
{
    self.data.assign ( right.data, self.flag, right.flag );
    self.flag = right.flag;

    return self;
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( optional&& right )
{
    self.data.assign ( std::move(right.data), self.flag, right.flag );
    self.flag = std::exchange ( right.flag, false );

    return self;
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( types right )
{
    self.data.assign ( std::move(right), self.flag );
    self.flag = true;

    return self;
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( nullopt_t )
{
    if ( flag )
    {
        data.clear();
        flag = false;
    }
}


// Conversion

template < class types >
constexpr optional<types>::operator types& ( )
{
    if ( not type() )
        throw type_error("bad optional access: cannot to get {} from {}, whose type == {}, has-value == false",
                         typeid(types), typeid(self), typeid(void));

    return data.get();
}

template < class types >
constexpr optional<types>::operator const types& ( ) const
{
    if ( not type() )
        throw type_error("bad optional access: cannot to get {} from {}, whose type == {}, has-value == false",
                         typeid(types), typeid(self), typeid(void));

    return data.get();
}

// Member

template < class types >
constexpr bool optional<types>::type ( ) const
{
    return flag;
}










/// Class optional::union_obj

// Declaration

/* In optional::union_obj, the flag and data are controlled seperately.
 * data.clear() will always do destroy_at, and std::move() will always
 * clear the storage of right one.
 */

template < class types >
union optional<types>::union_obj
{
    private:
        types type_storage;
        char void_storage;

    public:
        constexpr  union_obj ( );
        constexpr  union_obj ( const union_obj&,  bool );
        constexpr  union_obj (       union_obj&&, bool );
        constexpr  union_obj ( types );
        constexpr ~union_obj ( );
        constexpr  union_obj& assign ( const union_obj&,  bool, bool );
        constexpr  union_obj& assign (       union_obj&&, bool, bool );
        constexpr  union_obj& assign (       types,        bool );

    public:
        constexpr       union_obj& clear ( );
        constexpr       types&     get   ( );
        constexpr const types&     get   ( ) const;
};



// Implemention

template < class types >
constexpr optional<types>::union_obj::union_obj ( )
{

}

template < class types >
constexpr optional<types>::union_obj::union_obj ( const union_obj& init, bool init_flag )
{
    if ( init_flag )
        std::construct_at ( &type_storage, init.type_storage );
}

template < class types >
constexpr optional<types>::union_obj::union_obj ( union_obj&& init, bool init_flag )
{
    if ( init_flag )
        std::construct_at ( &type_storage, std::move(init.type_storage) );
}

template < class types >
constexpr optional<types>::union_obj::union_obj ( types init )
{
    std::construct_at ( &type_storage, std::move(init) );
}

template < class types >
constexpr optional<types>::union_obj::~union_obj ( )
{

}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::assign ( const union_obj& right, bool self_flag, bool right_flag )
{
    if ( self_flag and right_flag )
        type_storage = right.type_storage;

    else if ( self_flag and not right_flag )
        self.clear();

    else if ( not self_flag and right_flag )
        std::construct_at ( &type_storage, right.type_storage );

    /* else if ( not self_flag and not right_flag ): Do nothing. */

    return self;
}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::assign ( union_obj&& right, bool self_flag, bool right_flag )
{
    if ( self_flag and right_flag )
    {
        type_storage = std::move(right.type_storage);
        right.clear();
    }

    else if ( self_flag and not right_flag )
        self.clear();

    else if ( not self_flag and right_flag )
    {
        std::construct_at ( &type_storage, std::move(right.type_storage) );
        right.clear();
    }

    /* else if ( not self_flag and not right_flag ): Do nothing. */

    return self;
}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::assign ( types right, bool self_flag )
{
    if ( self_flag )
        type_storage = std::move ( right );
    else
        std::construct_at ( &type_storage, std::move ( right ) );

    return self;
}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::clear ( )
{
    std::destroy_at ( &type_storage );
    return self;
}

template < class types >
constexpr types& optional<types>::union_obj::get ( )
{
    return type_storage;
}

template < class types >
constexpr const types& optional<types>::union_obj::get ( ) const
{
    return type_storage;
}



