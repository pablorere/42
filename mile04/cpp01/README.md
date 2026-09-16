# C++ Module 01 — Memory allocation, pointers, references, switch

Focuses on stack vs heap allocation, the `new`/`delete` pair, references versus
pointers, pointers to members, and file streams.

## Exercises

| Dir | Name | Topic |
|-----|------|-------|
| `ex00` | BraiiiiiiinnnzzzZ | Stack vs heap `Zombie` creation (`newZombie`, `randomChump`) |
| `ex01` | Moar brainz! | Allocating an array of zombies (`zombieHorde`) |
| `ex02` | HI THIS IS BRAIN | References vs pointers to the same variable |
| `ex03` | Unnecessary violence | `Weapon`, `HumanA` (reference) and `HumanB` (pointer) |
| `ex04` | Sed is for losers | File copy with string replacement (`./Sed file s1 s2`) |
| `ex05` | Harl 2.0 | Member-function pointers / a log dispatcher |

## Build & run

```sh
cd ex00 && make && ./zombie
```

All exercises compile with `-Wall -Wextra -Werror -std=c++98`.
