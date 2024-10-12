#pragma once
#include "../../generic/math/interface.h"

namespace ap::spirit
{
    /// Parser
    template < class result_type > class numeric_expr;
    template < class result_type > class symbolic_expr;


    /// Include
    #include "numeric/numeric.h"
    #include "symbolic/symbolic.h"
}


#ifdef homework
namespace ap::spirit
{
    spirit::numeric_expr<double> ex;
    struct ex_init
    {
        ex_init()
        {
            ex.constant        ()["pi"]      = pi;
            ex.constant        ()["e"]       = e;
            ex.constant        ()["lyx"]     = 520;

            ex.nullary_function()["rand"]    = [] { return uniform_distribution(0.0, 1.0); };

            ex.unary_function  ()["abs"]     = [] (auto x) { return abs(x); };
            ex.unary_function  ()["sqrt"]    = [] (auto x) { return sqrt(x); };
            ex.unary_function  ()["floor"]   = [] (auto x) { return floor(x); };
            ex.unary_function  ()["ceil"]    = [] (auto x) { return ceil(x); };
            ex.unary_function  ()["round"]   = [] (auto x) { return round(x); };
            ex.unary_function  ()["exp"]     = [] (auto x) { return exp(x); };
            ex.unary_function  ()["ln"]      = [] (auto x) { return ln(x); };
            ex.unary_function  ()["sin"]     = [] (auto x) { return sin(degree(x)); };
            ex.unary_function  ()["cos"]     = [] (auto x) { return cos(degree(x)); };
            ex.unary_function  ()["tan"]     = [] (auto x) { return tan(degree(x)); };
            ex.unary_function  ()["arcsin"]  = [] (auto x) { return degree(arcsin(x)).value(); };
            ex.unary_function  ()["arccos"]  = [] (auto x) { return degree(arccos(x)).value(); };
            ex.unary_function  ()["arctan"]  = [] (auto x) { return degree(arctan(x)).value(); };

            ex.binary_function ()["max"]     = [] (auto x, auto y) { return std::max(x, y); };
            ex.binary_function ()["min"]     = [] (auto x, auto y) { return std::min(x, y); };
            ex.binary_function ()["mod"]     = [] (auto x, auto y) { return mod(x, y); };
            ex.binary_function ()["pow"]     = [] (auto x, auto y) { return pow(x, y); };
            ex.binary_function ()["log"]     = [] (auto x, auto y) { return log(x, y); };
        }
    };
    ex_init ex_init_instance;


    auto derivative_at ( const auto& f, auto p, auto prec )
    {
        return ( f(p+prec) - f(p-prec) ) / (2*prec);
    }

    auto newton_iterate ( const auto& f, auto p, int iter )
    {
        int it   = 0;
        let p2   = p;
        let prec = p;
        do
        {
            p    = p2;
            prec = 0.0000001;
            p2   = p - f(p) / derivative_at(f, p, prec);
        } while ( ap::abs(p - p2) >= prec and ++it <= iter );

        if ( it > iter )
            throw math_error("failed to solve equation (with attribute = {}) in {} iterations", typeid(decay<decltype(f)>), iter);

        return p2;
    }

    template < float_type type >
    constexpr type solve ( const function<type(type)>& f, int iter )
    {
        return newton_iterate(f, uniform_distribution<type>(type(-1), type(1)), iter);
    }




    auto cmd ( )
    {
        while(true)
        {
            std::cout << ">>> ";
            let str = input();

            // Calculate.
            if ( not str.contains('=') and not string(str).strip().begins_with("def") )
                try   { print(">>> {}\n"s.format(ex(str))); }
                catch ( const std::exception& e ) { print(">>> {}{}: {}\n"s.format(ap::abi::red, typeid(e), e.what())); }

            // Define constant.
            else if ( str.contains('=') and not string(str).strip().begins_with("solve") )
                try   { ex.constant()[string(str.partition('=')[1]).strip()] = ex(str.partition('=')[3]); print(); }
                catch ( const std::exception& e ) { print(">>> {}{}: {}\n"s.format(ap::abi::red, typeid(e), e.what())); }

            // Define f(x).
            else if ( string(str).strip().begins_with("def") and str.partition(':')[1].count(',') == 0 )
                try
                {
                    string prefix   = str.partition(':')[1];
                    string suffix   = str.partition(':')[3];
                    string fun_name = prefix[prefix.find("def")+3, prefix.find('(')-1];
                    string var_name = prefix[prefix.find('(')+1, prefix.right_find(')')-1];
                    fun_name.strip();
                    var_name.strip();

                    let f = numeric_expr<double(double)>();
                    f.variable        () = var_name;
                    f.constant        ().update(ex.constant        ());
                    f.nullary_function().update(ex.nullary_function());
                    f.unary_function  ().update(ex.unary_function  ());
                    f.binary_function ().update(ex.binary_function ());

                    ex.unary_function()[fun_name] = f(suffix);
                    print();
                }
                catch ( const std::exception& e ) { print(">>> {}{}: {}\n"s.format(ap::abi::red, typeid(e), e.what())); }

            // Define f(x,y).
            else if ( string(str).strip().begins_with("def") and str.partition(':')[1].count(',') == 1 )
                try
                {
                    string prefix     = str.partition(':')[1];
                    string suffix     = str.partition(':')[3];
                    string fun_name   = prefix[prefix.find("def")+3, prefix.find('(')-1];
                    string var_name   = prefix[prefix.find('(')+1, prefix.right_find(')')-1];
                    string var_name_1 = var_name.partition(',')[1];
                    string var_name_2 = var_name.partition(',')[3];
                    fun_name  .strip();
                    var_name_1.strip();
                    var_name_2.strip();

                    let f = numeric_expr<double(double,double)>();
                    f.variable        () = { var_name_1, var_name_2 };
                    f.constant        ().update(ex.constant        ());
                    f.nullary_function().update(ex.nullary_function());
                    f.unary_function  ().update(ex.unary_function  ());
                    f.binary_function ().update(ex.binary_function ());

                    ex.binary_function()[fun_name] = f(suffix);
                    print();
                }
                catch ( const std::exception& e ) { print(">>> {}{}: {}\n"s.format(ap::abi::red, typeid(e), e.what())); }

            // Define f(x, y, z...)
            else if ( string(str).strip().begins_with("def") and str.partition(':')[1].count(',') >= 2 )
                print(">>> {}{}: {}{}"s.format(ap::abi::red, typeid(expr_error), "currently only equal-or-less-than binary functions are supported", ap::abi::white));

            // Solve equation.
            else if ( string(str).strip().begins_with("solve") and str.contains('=') )
                try
                {
                    string var_name = str[str.find("solve")+5, str.find(':')-1];
                    string lhs = str[str.find(':')+1, str.find('=')-1];
                    string rhs = str[str.find('=')+1, -1];
                    var_name.strip();

                    let f = numeric_expr<double(double)>();
                    f.variable() = var_name;
                    f.constant        ().update(ex.constant        ());
                    f.nullary_function().update(ex.nullary_function());
                    f.unary_function  ().update(ex.unary_function  ());
                    f.binary_function ().update(ex.binary_function ());

                    let lhs_ex = f(lhs);
                    let rhs_ex = f(rhs);
                    let equation = [&] (auto x) { return lhs_ex(x) - rhs_ex(x); };
                    print(">>> {} = {}\n"s.format(var_name, solve<double>(equation, 10000)));
                }
                catch ( const std::exception& e ) { print(">>> {}{}: {}\n"s.format(ap::abi::red, typeid(e), e.what())); }
        }
    }
}

#endif
