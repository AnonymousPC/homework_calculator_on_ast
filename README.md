*This is a project extended from a school homework (which focuses on a scientific calculator, but later I implementioned some additional ones like variable declaration/assignment, function declaration/overload etc). It's a toy.*

# Purpose

A Python-interpreter implemented in C++ `boost::spirit`.

# Install

- Windows
    - Pre-compiled executable available at `bin/calculate.exe`
    - Or compile like this:
    ```bash
    g++ -std=c++23 -O3 -c main.cpp -o calculator.o
    g++ calculator.o bin/anonymous.dll -o main.exe
    ```

- Other
    - Requires a re-compile.


# Usage

```py
# Expression
- In : max(x, pi)^pi / log(tan(12), rand()) + abs(sqrt(e/2)) 
- Out: 3316679.525874111
```
```py
# Function
- In : def add_42(x): x + 42
- In : add_42(100)
- Out: 142
```
```py
# Overload
- In : def add_all(): 0
- In : def add_all(x): x
- In : def add_all(x, y): x + y
- In : def add_all(x, y, x): x + y + z
- In : add_all(42, 24)
- Out: 66
```
```py
# Assign
- In : x = 24
- In : y = 42
- In : x = y
- In : x
- Out: 42
```
```py
# More usage
- In : def rand_between(min, max): min + (max - min) * rand() 
- In : rand_between(100, 200) 
- Out: 149.83101221352834
```
```py
# More usage
- In : solve('x', "2x^2 - 4^x + 2 = 0") 
- Out: {'x', 1}
```
```py
# More usage
- In : solve('x', "max(x, x^x/2) * ln(abs(x-1)) - arctan(2^x) / exp(x) = x") 
- Out: {'x', 2.9165152495479694}
```
```py
# Syntax error handling
- In : Im not a legal statement!
- Out: parse_error: could not parse numeric_expr (with attribute = double(double)) "Im not a legal statement!" at pos 1
```
```py
# Math error handling
- In : sqrt(-1)
- Out: math_error: -1 is out of sqrt() domain [0,+inf)
```

