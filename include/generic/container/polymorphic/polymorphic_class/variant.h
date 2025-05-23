#pragma once

/// Auxiliary

namespace aux
{
    template < class... types >                   union union_of;
    template <                   class... types > constexpr bool all_different                                    = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr bool same_as_only_one_of                              = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr bool not_same_but_convertible_to_only_one_of          = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr bool not_convertible_but_constructible_to_only_one_of = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr bool not_same_but_assignable_to_only_one_of           = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr bool not_assignable_to_any_of                         = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr bool all_invocable_and_returns_same_type              = [] { static_assert(false, "you need to specialize it"); return false; } ();
}



/// Declaration

template < class... types >
class variant
{
    private: // Precondition
        static_assert ( sizeof...(types) >= 1 and aux::all_different<types...> );
        static_assert ( not ( is_const<types> or ... ) and not ( is_volatile<types> or ... ) and not ( is_reference<types> or ... ) );
        static_assert ( ( std::default_initializable<first_type_of<types...>> and ... and std::movable<types> ) ); // Does not requires all types to be default_constructible.

    private: // Typedef
        using union_obj = aux::union_of<types...>;

    private: // Data
        union_obj data;
        int       flag = 0;

    public: // Typedef
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) )
        using value_type = index_type_of<index,types...>;

    public: // Core
        constexpr          variant ( );
        constexpr          variant ( const variant&  )             requires ( std::copyable<types> and ... );
        constexpr          variant (       variant&& );
        constexpr          variant (       auto  val )             requires aux::same_as_only_one_of                             <decay<decltype(val)>,types...>;
        constexpr          variant ( const auto& val )             requires aux::not_same_but_convertible_to_only_one_of         <decay<decltype(val)>,types...>;
        constexpr explicit variant ( const auto& val )             requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(val)>,types...>;
        constexpr         ~variant ( );
        constexpr          variant& operator = ( const variant&  ) requires ( std::copyable<types> and ... );
        constexpr          variant& operator = (       variant&& );
        constexpr          variant& operator = (       auto  val ) requires aux::same_as_only_one_of                             <decay<decltype(val)>,types...>;
        constexpr          variant& operator = ( const auto& val ) requires aux::not_same_but_assignable_to_only_one_of          <decay<decltype(val)>,types...>;
        constexpr          variant& operator = (       auto  val ) requires aux::not_assignable_to_any_of                        <decay<decltype(val)>,types...> = delete; // Explicitly deleted, e.x. char[5] to int (which is constructible but not assignable and is not expected).

    public: // Operator
        template < class result_type > constexpr operator       result_type& ( )       requires aux::same_as_only_one_of<result_type,types...>;
        template < class result_type > constexpr operator const result_type& ( ) const requires aux::same_as_only_one_of<result_type,types...>;

    public: // Member
        constexpr int type ( ) const;

    public: // Visit
        constexpr decltype(auto) visit ( auto&& visitor )       requires aux::all_invocable_and_returns_same_type<decltype(visitor),      types&...>;
        constexpr decltype(auto) visit ( auto&& visitor ) const requires aux::all_invocable_and_returns_same_type<decltype(visitor),const types&...>;
};



#include "variant.cpp"


