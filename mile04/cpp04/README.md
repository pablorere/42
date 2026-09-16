# C++ Module 04 — Subtype polymorphism, abstract classes, interfaces

The module where C++ becomes genuinely object-oriented: virtual functions and
vtables, abstract classes (pure virtual), deep copies and ownership, and
interfaces.

## Exercises

| Dir | Name | Topic |
|-----|------|-------|
| `ex00` | Polymorphism | `Animal`/`Dog`/`Cat`, `virtual` and slicing; `WrongAnimal` shows the pitfall |
| `ex01` | I don't want to set the world on fire | `Brain`, deep copy, Rule of Three |
| `ex02` | Abstract class | `AAnimal` (pure virtual) cannot be instantiated |
| `ex03` | Interface & recap | `AMateria`/`Ice`/`Cure`, `ICharacter`, `Character`, `MateriaSource` |

## Build & run

```sh
cd ex00 && make && ./animal
cd ex01 && make && ./animal
cd ex02 && make && ./animal
cd ex03 && make && ./interface
```

Compiled with `-Wall -Wextra -Werror -std=c++98`.
