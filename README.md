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
   
   
   

