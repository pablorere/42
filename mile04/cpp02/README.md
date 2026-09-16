# C++ Module 02 — Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form

Builds a fixed-point number class step by step, covering the Orthodox Canonical
Form (default ctor, copy ctor, copy assignment, destructor), conversion
operators, and overloaded comparison/arithmetic operators.

## Exercises

| Dir | Name | Topic |
|-----|------|-------|
| `ex00` | My First Class in Orthodox Canonical Form | `Fixed` with `int` raw bits and `10` fractional bits |
| `ex01` | Towards a more useful fixed-point number class | `int`/`float` constructors, `toFloat`, `toInt`, `operator<<` |
| `ex02` | Now we're talking | Comparison, arithmetic, increment/decrement, `min`/`max` |

## Build & run

```sh
cd ex00 && make && ./fixed_test
cd ex01 && make && ./Towards_a_more_useful_fixed_point_number_class
cd ex02 && make && ./now_were_talking
```

Compiled with `-Wall -Wextra -Werror -std=c++98`.
