This is a homework-oriented project hoping to create a Python-like scientific calculator.

1. Environment
   If you try to run this project on Windows platfrom, it has been compiled into ./bin/calculate.exe.
   Click it directly and everything goes ok. The depended dynamic-linked libraries are all listed in ./lib.

   On other platforms a re-compile is needed. We use g++ compiler to directly compile it. CMake is choosable but not hard-required.
   
   [[requirement]] gcc/g++ version >= 14.0
   [[requirement]] stdc++exp
   [[requirement]] boost.locale
   [[requirement]] boost.thread
   [[requirement]] boost.spirit
   [[requirement]] eigen.dense
   [[requirement]] oneapi.tbb

   Input these command-lines to compile main.cpp:
     '''g++ -std=c++23 -O3 -c main.cpp -o calculator.o'''
   and this line to link and generate executable file:
     '''g++ -o main.o -s bin/anonymous.dll bin/libboost_locale-mt.dll bin/libboost_thread-mt.dll libtbb12.dll'''
   replace 'dll' with your system-preferred shared library suffix, such as '.so' on Linux.


2. Usage
   Calculator is best learned by examples.

   >>> 1+2

   >>> 3


   >>> sin(30*3)

   >>> 1


   >>> x=123

   >>> max(x, pi)^pi / log(tan(12), rand()) + abs(sqrt(e/2))

   >>> 3316679.525874111


   >>> def rand_between(min, max): min + (max - min) * rand()

   >>> rand_between(100, 200)

   >>> 149.83101221352834


   >>> solve x: 2x^2 - 4^x + 2 = 0

   >>> x = 1

   
   >>> solve x: max(x, x^x/2) * ln(abs(x-1)) - arctan(2^x) / exp(x) = x

   >>> x = 2.9165152495479694


   >>> def func(x): 100 + x + hahahaha, i'm not 42 and i'm 24

   >>> ap::expr_error: failed to parse numeric_expr " 100 + x + hahahaha, i'm not 42 and i'm 24" at pos 10 (with attribute = double (double))


   >>> param = 42

   >>> solve abc: param * abc + rand() = 100

   >>> ap::math_error: failed to solve equation (with attribute = ap::function<double (double)>) in 10000 iterations


   You can also use 'calculate 100+200' in command line and get '300' once you put calculate.exe into system.environment_variables.PATH (on Windows).


3. Extension
   This project uses C++.
   
   Include the header files:
   #include <your/path/to/include/specific/spirit/interface.h>
   and link the implement libaries
   g++ ... (link) your/path/to/anonymous.dll.

   The main class is template <typename attribute_type> class ap::spirit::numeric_expr. It has following public member-functions:
   **attribute_type numeric_expr::operator() (string) const**
   **Accepts** a expr_string.
   **Returns** its value.
   **Throws** ap::expr_error (extends from std::exception) if the string is not parsable.
   For example:
      numeric_expr<float> expr; expr("2+3"); // returns 5 (type = float).
      numeric_expr<double(double)> expr; expr.variable()='x'; expr("x+2"); // returns a function which function(2) == 4.


   **map<string,number_type>           numeric_expr::constant() // if attribute_type is a function**
   **map<string,nullary_function_type> numeric_expr::nullary_function()**
   **map<string,unary_function_type>   numeric_expr::unary_function()**
   **map<string,binary_function_type>  numeric_expr::binary_function()**
   **Returns** the map which stores the functions. Keys are the substring in where input expression are expected to be parsed, and values are functions which the generator should do.
   **Throws** ap::key_error if try to visit an non-existent constant/function via **const** numeric_expr.
   For example:
      numeric_expr<float> expr; expr.unary_function()["sin"] = [] (auto x) { return std::sin(x); }; // registers a function, if the parser meets sin(...expr) then do sin(value-of-expr) in generator.
   Refresh the registered constant/function if keys are repeated.

   **auto numeric_expr::variable() // returns string if attribute_type is unary_function, pair<string> if binary, and deleted if not function-type**
   **Returns** the strings which should be parsed as a variable.
   **noexcept**
   **Undefined behavior** if exist key1 in variable().keys() and key2 in constant().keys() | xxx_function().keys() => key1 == key2.   
   

4. Bug report
   On Windows, if you found any bug or unexpected behavior, re-input it into calculate_debug.exe. Get the stacktrace from the output then post it to commitments.
   for example:
   
   [[calculate.exe]]
   >>> def func(x, y): x + z
   >>> ap::expr_error: failed to parse numeric_expr " x + z" at pos 4 (with attribute = double (double, double))
      at main in F:/Code/Anonymous/main.cpp:14
      at ap::spirit::cmd() in F:/Code/specific/spirit/interface.h:148
      at ap::spirit::numeric_expr<double (double, double)>::operator()(ap::basic_string<char> const&) const in F:/Code/specific/spirit/numeric/numeric.cpp:582
   and we'll soon fix it.
   
   On Linux, re-compile the project with:
     '''g++ -std=c++23 -c main.cpp -o calculator.o'''
   
   
   

