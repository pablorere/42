# C++ Module 00 — Namespaces, classes, member functions, iostream

First C++ module of the 42 curriculum. Introduces classes, member functions,
`std::string`, `std::cout`/`std::cin`, and the `static`/non-member distinction.

## Exercises

| Dir | Name | Topic |
|-----|------|-------|
| `ex00` | megaphone | Argument handling, `std::cout`, a small `ToUpper` class |
| `ex01` | phonebook | A CRUD phonebook capped at 8 contacts |
| `ex02` | Account | Reconstructing a class from its header + reference log |

## Build & run

```sh
cd ex00 && make && ./megaphone "hello"
cd ex01 && make && ./Phonebook
cd ex02 && make && ./account
```

Each exercise uses `c++` with `-Wall -Wextra -Werror -std=c++98`.
