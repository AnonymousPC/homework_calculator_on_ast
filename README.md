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
- In : max(x, pi)^pi / log(tan(12), rand()) + abs(sqrt(e/2)) 
- Out: 3316679.525874111
```
```py
- In : def rand_between(min, max): min + (max - min) * rand() 
- In : rand_between(100, 200) 
- Out: 149.83101221352834
```
```py
- In : solve x: 2x^2 - 4^x + 2 = 0 
- Out: x = 1
```
```py
- In : solve x: max(x, x^x/2) * ln(abs(x-1)) - arctan(2^x) / exp(x) = x 
- Out: x = 2.9165152495479694
```
