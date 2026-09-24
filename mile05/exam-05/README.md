# Exam Rank 05 — Guia de Estudo (Level 1)

> Guia denso para as três provas de **Level 1** do 42cursus Exam Rank 05:
> `polyset`, `bigint`, `vect2`. Cada prova tem **esqueleto guiado** + **solução
> completa comentada** + **armadilhas**.
>
> Fonte do enunciado: https://github.com/Mohaben-1/42-Exam-Rank-05 (branch `Medd`).

---

## Como o exam funciona

- O exam sorteia **um** assignment. Level 1 tem 3 possíveis: `polyset`, `bigint`,
  `vect2`. Level 2 tem `bsq` e `life`.
- Você recebe uma pasta com o **subject** (enunciado) e arquivos já fornecidos
  (`main.cpp`, headers, classes-base). Você cria **apenas os arquivos pedidos**.
- Regra transversal em quase toda prova de C++ do exam: **Orthodox Canonical
  Form** (OCF) em todas as classes + **`const` correto**.
- É avaliado rodando o `main.cpp` fornecido. Se ele compila e o comportamento
  bate, passou. Otimização normalmente **não** importa.

## Ordem sugerida de estudo

| Ordem | Prova      | Dificuldade | Por que nessa ordem |
|-------|------------|-------------|---------------------|
| 1     | `vect2`    | ★★          | Só operadores; aquece sobrecarga sem memória dinâmica. |
| 2     | `bigint`   | ★★★         | Operadores + aritmética manual (carry) + `std::vector`. |
| 3     | `polyset`  | ★★★★        | Herança múltipla, `virtual`, abstratas, referência como membro. É o mais "de C++". |

Se for estudar em blocos: faça `00-fundamentos-cpp.md` primeiro — ele cobre o
que as três provas cobram de OOP.

## Arquivos deste guia

| Arquivo | Conteúdo |
|---------|----------|
| `00-fundamentos-cpp.md` | OCF, abstratas, herança múltipla + `virtual`, const-correctness, `delete`/`delete[]`. Base comum. |
| `01-polyset.md` | Prova `polyset`: `searchable_array_bag`, `searchable_tree_bag`, `set`. |
| `02-bigint.md` | Prova `bigint`: precisão arbitrária, carry, digitshift, comparações. |
| `03-vect2.md` | Prova `vect2`: sobrecarga completa de operadores em vetor 2D. |
| `99-checklist-prova.md` | Auditoria final antes de submeter. |

## Compilação rápida (genérico)

```sh
# dentro da pasta do exercise, com o main.cpp fornecido
g++ -Wall -Wextra -Werror -std=c++98 *.cpp -o prog
./prog
```

> As soluções deste guia foram **compiladas e executadas** com o `main.cpp`
> original de cada subject usando `-Wall -Wextra -Werror -std=c++98`.

## Regras de submissão (padrão 42 exam)

- Nome do assignment: exatamente o do subject (`polyset`, `bigint`, ...).
- Entregar **somente** os arquivos em `Expected files`.
- Nunca usar funções proibidas pelo subject (cada prova pode ter lista própria).
- Sem `main` seu — o do subject manda.
