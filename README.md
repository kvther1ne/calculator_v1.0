# calculator_v1.0

## Implementation of SmartCalc v1.0.

In this project I implemented an extended version of the usual calculator, which can be found in the standard applications of each operating system in the C programming language using structured programming. In addition to basic arithmetic operations such as add/subtract and multiply/divide, it can calculate arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.).
Besides calculating expressions, it also supports the use of the x variable and the graphing of the corresponding function.

The SmartCalc v1.0 program implemented:
- The program built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, test, gcov_report
- Prepared full coverage of modules related to calculating expressions with unit-tests using the Check library
- GUI implementation, based on Qt
- Both integers and real numbers with a dot can be input into the program
- The calculation must be done after you complete entering the calculating expression and press the = symbol.
- Calculating arbitrary bracketed arithmetic expressions in infix notation
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable x as a number
- Plotting a graph of a function given by an expression in infix notation with the variable x (with coordinate axes, mark of the used scale and an adaptive grid)
- Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000
- Verifiable accuracy of the fractional part is at least to 7 decimal places
- Bracketed arithmetic expressions in infix notation must support the following arithmetic operations and mathematical functions:
- 
| Operator name | Infix (classic) notation | Prefix (Polish) notation | Postrix (reverse Polish) notation |
| ------------- |:------------------:|:----------------------:|:----------------:|:----------------:|
| Addition    |  +   | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
