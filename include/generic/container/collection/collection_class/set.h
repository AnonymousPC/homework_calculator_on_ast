#pragma once

template < class type, class less, class container >
class basic_set
    extends public collection_algo<basic_set<type,less,container>,type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );
        static_assert ( function_type<less,bool(type,type)> );

    private: // Data
        container data = container();

    public: // Typedef
        using  key_type       = type;
        using  value_type     = type;
        using  iterate_type   = type;
        using  compare_type   = less;
        using  container_type = container;
        using  const_iterator = container::const_iterator;
        struct set_tag { };

    public: // Core
        constexpr           basic_set ( ) = default;
        constexpr           basic_set ( std::initializer_list<type>&& );
        constexpr explicit  basic_set ( std::from_range_t, std::ranges::input_range auto&& r ) requires requires { std::declval<basic_set>().push(*r.begin()); };

    public: // Conversion
        constexpr       auto& data_handle ( );
        constexpr const auto& data_handle ( ) const;

    public: // Interface
        constexpr  int              size        ( )                            const;
        constexpr  bool             empty       ( )                            const;
        constexpr  const_iterator   begin       ( )                            const;
        constexpr  const_iterator   end         ( )                            const;

        constexpr  basic_set&       clear       ( );
        constexpr  bool             contains    ( const type& )                const;
        constexpr  basic_set&       push        (       type  );
        constexpr  basic_set&       pop         ( const type& );
        constexpr  basic_set&       update      ( const set_type<type> auto& );
};

#include "set.cpp"
