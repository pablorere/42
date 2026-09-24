# Soluções prontas (validadas)

Código compilado e executado contra o `main.cpp` original de cada subject com:

```sh
g++ -Wall -Wextra -Werror -std=c++98 <main+solucao> -o prog
```

## O que copiar para o exam

| Prova | Arquivos que VOCÊ entrega (aqui) | Arquivos que o subject já fornece |
|-------|----------------------------------|-----------------------------------|
| `polyset` | `searchable_array_bag.{hpp,cpp}`, `searchable_tree_bag.{hpp,cpp}`, `set.{hpp,cpp}` | `bag.hpp`, `searchable_bag.hpp`, `array_bag.{hpp,cpp}`, `tree_bag.{hpp,cpp}`, `main.cpp` |
| `bigint` | `bigint.{hpp,cpp}` | `main.cpp` |
| `vect2` | `vect2.{hpp,cpp}` | `main.cpp` |

## Compilar

```sh
# polyset
g++ -Wall -Wextra -Werror -std=c++98 *.cpp -o polyset && ./polyset 5 3 5 1 9 3 7

# bigint
g++ -Wall -Wextra -Werror -std=c++98 main.cpp bigint.cpp -o bigint && ./bigint

# vect2
g++ -Wall -Wextra -Werror -std=c++98 main.cpp vect2.cpp -o vect2 && ./vect2
```

> As saídas esperadas estão no fim de cada guia (`01`..`03`).
