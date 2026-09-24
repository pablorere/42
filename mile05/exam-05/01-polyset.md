# 01 — Prova `polyset`

> Assignment: `polyset`
> Expected files: `searchable_array_bag.cpp`, `searchable_array_bag.hpp`,
> `searchable_tree_bag.cpp`, `searchable_tree_bag.hpp`, `set.cpp`, `set.hpp`

## Enunciado (resumo fiel)

Na pasta você recebe:

- `bag` — classe **abstrata** representando um saco (multiconjunto).
- `searchable_bag` — abstrata, bag **com busca**.
- `array_bag` — implementação de bag usando **array**.
- `tree_bag` — implementação de bag usando **árvore binária de busca (BST)**.

**Primeira parte.** Implementar `searchable_array_bag` e `searchable_tree_bag`
que herdam de `array_bag` / `tree_bag` (respectivamente) **e** implementam a
abstrata `searchable_bag`.

**Segunda parte.** Implementar `set`, que embrulha um `searchable_bag` e o
transforma em um **conjunto** (sem duplicatas).

Regras: **todas as classes em OCF**, **`const` correto**, otimização não importa.
O `main.cpp` fornecido tem que compilar com o seu código.

### Bag vs Set (arquivo `shame.en.txt`)

- **Set**: guarda valores **únicos**, sem ordem particular. Testa-se **pertencimento**.
- **Bag / multiset**: permite **repetidos** (duplicatas).

Ou seja: a diferença prática que você implementa é **"inserir só se ainda não
existe"** dentro do `set`.

---

## Arquivos fornecidos (NÃO recriar)

### `bag.hpp` (abstrata raiz)

```cpp
class bag
{
public:
    virtual void insert(int) = 0;
    virtual void insert(int *, int) = 0;
    virtual void print() const = 0;
    virtual void clear() = 0;
};
```

### `searchable_bag.hpp` (abstrata, filha de bag)

```cpp
class searchable_bag : virtual public bag
{
public:
    virtual bool has(int) const = 0;
};
```

### `array_bag.hpp` (membros `protected`: `int *data; int size;`)

```cpp
class array_bag : virtual public bag {
protected:
    int *data;
    int size;
public:
    array_bag();
    array_bag(const array_bag &);
    array_bag &operator=(const array_bag &other);
    ~array_bag();
    void insert(int);
    void insert(int *, int);
    void print() const;
    void clear();
};
```

### `tree_bag.hpp` (BST; `protected` `struct node {node *l,*r; int value;}` e `node *tree;`)

```cpp
class tree_bag : virtual public bag {
protected:
    struct node { node *l; node *r; int value; };
    node *tree;
public:
    tree_bag();
    tree_bag(const tree_bag &);
    tree_bag &operator=(const tree_bag &);
    ~tree_bag();
    node *extract_tree();
    void set_tree(node *);
    virtual void insert(int);
    virtual void insert(int *array, int size);
    virtual void print() const;
    virtual void clear();
private:
    static void destroy_tree(node *);
    static void print_node(node *);
    static node *copy_node(node *);
};
```

**Leia os `protected`:** `data`/`size` e `tree` estão acessíveis nas suas
subclasses. É por isso que `has()` consegue varrer `data[i]` e navegar na `tree`
sem getters. **Não** recrie nem duplique esses membros.

---

## Parte 1 — `searchable_array_bag` / `searchable_tree_bag`

### O que herdar

```cpp
class searchable_array_bag : public array_bag, public searchable_bag { ... };
class searchable_tree_bag  : public tree_bag,  public searchable_bag { ... };
```

- Herda o **concreto** (`array_bag` / `tree_bag`) → ganha `insert`, `print`, `clear`.
- Herda o **abstrato** (`searchable_bag`) → é obrigada a implementar `has` e passa
  a ser tratável como `searchable_bag*` no `main`.
- `searchable_bag` e `array_bag` herdam `bag` de forma virtual → uma única `bag`.

### Esqueleto guiado

1. No `.hpp`: inclua o header do pai concreto **e** `searchable_bag.hpp`; declarar
   OCF (4 funções) + `bool has(int) const;`.
2. No `.cpp`, os construtores de cópia e `operator=` **delegam ao pai**:
   `: array_bag(copy)` e `array_bag::operator=(copy)`.
3. `has`:
   - array → varredura linear em `data[0..size-1]`.
   - árvore → busca binária guiada por `<` / `>` em `node->value`.

### Solução comentada — `searchable_array_bag.hpp`

```cpp
#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag
{
public:
    searchable_array_bag();
    searchable_array_bag(const searchable_array_bag &copy);
    searchable_array_bag &operator=(const searchable_array_bag &copy);
    ~searchable_array_bag();

    bool has(int value) const;
};

#endif
```

### `searchable_array_bag.cpp`

```cpp
#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() {}

searchable_array_bag::searchable_array_bag(const searchable_array_bag &copy)
    : array_bag(copy) {}                    // delega a cópia ao pai

searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &copy)
{
    if (this != &copy)                      // proteção contra auto-atribuição
        array_bag::operator=(copy);         // delega ao pai
    return (*this);
}

searchable_array_bag::~searchable_array_bag() {}

bool searchable_array_bag::has(int value) const
{
    for (int i = 0; i < size; i++)
        if (data[i] == value)               // data/size são protected do pai
            return (true);
    return (false);
}
```

### `searchable_tree_bag.hpp`

```cpp
#ifndef SEARCHABLE_TREE_BAG_HPP
#define SEARCHABLE_TREE_BAG_HPP

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag
{
public:
    searchable_tree_bag();
    searchable_tree_bag(const searchable_tree_bag &copy);
    searchable_tree_bag &operator=(const searchable_tree_bag &copy);
    ~searchable_tree_bag();

    bool has(int value) const;
};

#endif
```

### `searchable_tree_bag.cpp`

```cpp
#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &copy)
    : tree_bag(copy) {}

searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &copy)
{
    if (this != &copy)
        tree_bag::operator=(copy);
    return (*this);
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int value) const
{
    node *current = tree;                   // tree é protected do pai
    while (current)
    {
        if (current->value == value)
            return (true);
        else if (value < current->value)
            current = current->l;           // menor → esquerda
        else
            current = current->r;           // maior/igual → direita
    }
    return (false);
}
```

> **Por que `<` e não `<=`?** O `tree_bag::insert` fornecido manda `<` para a
> esquerda e `>=` para a direita. O `has` precisa usar exatamente a **mesma
> regra de ordenação**, senão a busca descarta o ramo errado.

---

## Parte 2 — `set`

### Esqueleto guiado

- Membro: **referência** `searchable_bag &bag;` (o set **não possui** a bag — só a
  usa). Por isso não há cópia do bag no destrutor.
- `insert(int)`: só insere se `!bag.has(value)`.
- `insert(int*, int)`: idem para cada elemento.
- `print`, `clear`, `has`: **delegam** para `bag`.
- `get_bag() const` → devolve `const searchable_bag &`.
- **OCF**: construtor padrão não faz sentido (precisa da referência), então só
  construtor com parâmetro, cópia e destrutor. O `operator=` é o ponto delicado.

### Por que o `set` quase não tem OCF clássico

Vide `00-fundamentos-cpp.md` §4: membro **referência** não pode ser re-seatado.
Logo `set &operator=(const set&)` não consegue trocar o bag apontado. Opções:

1. **Omitir** o `operator=` (o compilador gera um implicitamente **deletado**
   porque há membro referência). O `main` não usa atribuição de `set`. ✔ abordagem do repo.
2. Declarar `set &operator=(const set&) = delete;` explicitamente para deixar claro.

O que **não** vale: fingir que copia a referência (não dá).

### `set.hpp`

```cpp
#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
private:
    searchable_bag &bag;                    // referência: set NÃO é dono da bag
public:
    set(searchable_bag &_bag);
    set(const set &copy);
    ~set();

    void insert(int value);
    void insert(int *arr, int size);
    void print() const;
    void clear();

    bool has(int value) const;

    const searchable_bag &get_bag() const;
};

#endif
```

### `set.cpp`

```cpp
#include "set.hpp"

set::set(searchable_bag &_bag) : bag(_bag) {}

set::set(const set &copy) : bag(copy.bag) {}   // copia a REFERÊNCIA (mesmo bag)

set::~set() {}                                 // não destrói a bag

void set::insert(int value)
{
    if (!bag.has(value))                       // regra central do set
        bag.insert(value);
}

void set::insert(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        if (!bag.has(arr[i]))
            bag.insert(arr[i]);
}

void set::print() const  { bag.print(); }

void set::clear()        { bag.clear(); }

bool set::has(int value) const { return (bag.has(value)); }

const searchable_bag &set::get_bag() const { return (bag); }
```

---

## Como o `main.cpp` exercita tudo

```cpp
searchable_bag *t = new searchable_tree_bag;   // polimorfismo: base ← derivado
searchable_bag *a = new searchable_array_bag;
for (...) { t->insert(atoi(av[i])); a->insert(atoi(av[i])); }
t->print(); a->print();
for (...) {
    std::cout << t->has(atoi(av[i]))     << std::endl;  // existe?
    std::cout << a->has(atoi(av[i]))     << std::endl;
    std::cout << t->has(atoi(av[i]) - 1) << std::endl;  // vizinho (talvez não)
    std::cout << a->has(atoi(av[i]) - 1) << std::endl;
}
t->clear(); a->clear();
const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a)); // cópia const
tmp.print(); tmp.has(1);                        // precisa do has() const
set sa(*a); set st(*a);                         // dois sets sobre a MESMA bag
for (...) { st.insert(...); sa.insert(...); }   // set deduplica
sa.has(atoi(av[1])); sa.print();
sa.get_bag().print();                           // get_bag() const → print() const
st.print();
sa.clear();
int arr[] = {1,2,3,4}; sa.insert(arr, 4);
```

Detalhes que o `main` **força**:

- `const searchable_array_bag tmp(...)` + `tmp.has(1)` → `has` tem que ser `const`.
- `sa.get_bag().print()` → `get_bag` devolve `const&` e `print` é `const`.
- `static_cast<searchable_array_bag&>(*a)` → cópia concreta; seu ctor de cópia
  tem que existir e copiar o array (deep copy do pai).
- `set sa(*a); set st(*a);` → ambos compartilham a mesma `a`; ordem de inserção
  difere por causa da deduplicação.

## Armadilhas (leia antes da prova)

1. **Não reimplemente** `insert`/`print`/`clear` nas subclasses de busca — o pai
   já faz. Só `has` é nova.
2. Esquecer `: array_bag(copy)` / `tree_bag(copy)` no ctor de cópia → cópia rasa
   ou membros não inicializados.
3. `has` da árvore usando `<=` em vez de `<` (ou vice-versa) → busca errada.
4. `operator=` sem `if (this != &copy)`.
5. Marcar `has` sem `const` → quebra por causa do objeto `const tmp`.
6. `set` recebendo a bag **por valor** em vez de referência → slicing + o
   `get_bag` não refletiria o original.
7. Tentar definir `operator=` do `set` sem perceber que a referência não pode ser
   re-seatada.

## Compilar e validar

```sh
mkdir -p polyset && cd polyset
# copie: bag.hpp searchable_bag.hpp array_bag.* tree_bag.* main.cpp  (do subject)
# + os 6 arquivos que você escreveu
g++ -Wall -Wextra -Werror -std=c++98 *.cpp -o polyset
./polyset 5 3 5 1 9 3 7
```

Saída exata esperada (com esses argumentos, 34 linhas):

```text
1 3 3 5 5 7 9        <- linha 1: t->print()  (tree, in-order: ordenado, com duplicatas)
5 3 5 1 9 3 7        <- linha 2: a->print()  (array, ordem de inserção)
                     (linhas 3..30: 28 x has() → 1/0)
                     (linha 31: vazia — tmp.print() de a JÁ limpo → array vazio)
5 3 1 9 7            <- linha 32: sa.print()  (set sobre `a`, SEM duplicatas)
5 3 1 9 7            <- linha 33: sa.get_bag().print()
5 3 1 9 7            <- linha 34: st.print()
```

Pontos de atenção que essa saída revela:

- **`tmp` foi copiado DEPOIS de `a->clear()`** → imprime vazio (linha 31). Isso
  testa que sua cópia não "vaza" dados antigos.
- **`t` (tree) imprime ordenado** (in-order); `a` (array) imprime na ordem de
  inserção. São estruturas diferentes.
- **`sa` e `st` wrappam o MESMO `*a`** (o `main` passa `*a` para os dois). Por
  isso ambas imprimem a mesma coisa (array deduplicado) — não é bug, é o `main`.
- `sa.insert(arr, 4)` no fim roda sobre a bag já limpa e não imprime nada.
