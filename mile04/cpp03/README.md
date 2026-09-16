# C++ Module 03 — Inheritance

Introduces inheritance in C++: construction/destruction order, access specifiers,
name hiding, and the diamond problem with virtual inheritance.

## Exercises

| Dir | Name | Topic |
|-----|------|-------|
| `ex00` | Aaaaand... OPEN! | `ClapTrap` with attack, damage and repair |
| `ex01` | Serena, my love! | `ScavTrap` inherits from `ClapTrap` |
| `ex02` | Repetitive work | `FragTrap` joins, plus `ScavTrap` |
| `ex03` | Now it's weird! | `DiamondTrap` using virtual inheritance |

Sources live in `srcs/` with headers in `inc/`.

## Build & run

```sh
cd ex00 && make && ./ClapTrap00
```

Compiled with `-Wall -Wextra -Werror -std=c++98`.
