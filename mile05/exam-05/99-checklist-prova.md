# 99 — Checklist final antes de submeter

Use isto nos últimos 10 minutos de qualquer uma das provas. Marque cada item.

## Compilação

- [ ] Compila **sem erros** com o `main.cpp` original:
      `g++ -Wall -Wextra -Werror -std=c++98 *.cpp -o prog`
- [ ] Nenhum warning (o exam pode não usar `-Werror`, mas warning costuma
      indicar bug real: variável não inicializada, retorno faltando, etc.).
- [ ] Nenhum arquivo a mais nem a menos que o `Expected files`.
- [ ] Sem `main()` seu.
- [ ] Sem funções proibidas pela prova.

## OCF (Orthodox Canonical Form)

- [ ] Toda classe tem as 4 funções: padrão, cópia, `operator=`, destrutor.
- [ ] `operator=` trata auto-atribuição (`if (this != &other)`).
- [ ] Para classes com **referência** membro (`set`): `operator=` intencional
      (omitido/deletado) — decisão consciente, não esquecimento.
- [ ] Cópia é **profunda** quando há ponteiro (`array_bag`); delegada ao pai
      quando a classe só estende comportamento (`searchable_*`).

## const-correctness

- [ ] `has(int) const` — senão `const tmp.has(1)` não compila.
- [ ] `print() const`, `get_bag() const`.
- [ ] `operator[]` tem **duas** versões (const e não-const) → `vect2`.
- [ ] Parâmetros de cópia são `const T&`.

## Herança (só `polyset`)

- [ ] `searchable_array_bag : public array_bag, public searchable_bag`.
- [ ] `searchable_tree_bag : public tree_bag, public searchable_bag`.
- [ ] Herança `virtual public bag` preservada nos pais (não mexi nos headers).
- [ ] **Não** reimplementei `insert`/`print`/`clear` nas subclasses de busca.
- [ ] `has` da árvore usa a **mesma** regra do `insert` (`<` esquerda, `>=` direita).

## Semântica específica

- [ ] `set::insert` só insere se `!bag.has(value)` (sem duplicatas).
- [ ] `set` guarda a bag por **referência**, não por valor.
- [ ] `bigint` tem as **4** sobrecargas de shift (`int` e `bigint`, `<<` e `>>`)
      e `<<=`/`>>=`.
- [ ] `bigint` **não** imprime zeros à esquerda; `0 << n` continua `0`.
- [ ] `vect2` tem `operator*(int, const vect2&)` livre para `3 * v`.
- [ ] `vect2` pós-`++`/`--` devolve o valor **antigo**.
- [ ] `vect2` imprime exatamente `{x, y}`.

## Comportamento (rodei de verdade)

- [ ] Executei com vários argumentos/entradas e conferi o output.
- [ ] Rodei pelo menos um caso de **duplicatas** (`polyset`) e um de **shift
      encadeado** (`bigint`).
- [ ] Sem *crash* / sem *segfault*.

## Cinto de segurança mental

- [ ] Se travar, releia o `main` primeiro — ele **é** a especificação.
- [ ] Não otimize. "The optimization of your code isn't important."
- [ ] Prefira código simples e correto a código elegante e quebrado.

---

## Cola de 30 segundos por prova

| Prova | O que realmente implementar |
|-------|-----------------------------|
| `polyset` | 2 subclasses (`has` linear / `has` BST) + `set` que deduplica delegação. OCF delegando ao pai. |
| `bigint` | vector de dígitos little-endian + `+` com carry + shifts (`int` e `bigint`) + comparações + `<<` stream. |
| `vect2` | 2 ints + todos os operadores aritméticos + `[]` duplo + `<<` no formato `{x, y}`. |
