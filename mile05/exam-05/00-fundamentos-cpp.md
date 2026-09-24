# 00 — Fundamentos de C++ que as 3 provas cobram

Esta é a base comum. Se você dominar os 8 tópicos abaixo, `polyset`, `bigint` e
`vect2` viram aplicação direta.

---

## 1. Classes abstratas e funções virtuais puras

```cpp
class bag
{
public:
    virtual void insert(int) = 0;      // puro → bag é abstrata
    virtual void insert(int *, int) = 0;
    virtual void print() const = 0;
    virtual void clear() = 0;
};
```

- `= 0` (pura) torna a classe **abstrata**: você **não pode** instanciar `bag`.
- Uma classe que herda e **não** implementa todas as puras continua abstrata.
- Só é possível usá-la via ponteiro/referência (dispatch dinâmico).

**Ponto crítico do polyset:** `bag` **não** tem destrutor virtual. `delete` num
ponteiro de base com destrutor não-virtual é UB. O `main` não deleta, então passa.
Não é seu trabalho corrigir a classe fornecida — mas **saiba apontar** isso na
defesa.

---

## 2. Herança múltipla e herança `virtual` (o diamante)

No polyset, a hierarquia vira:

```
        bag            bag
         |              |
     array_bag   searchable_bag
          \            /
     searchable_array_bag
```

Como `array_bag` e `searchable_bag` herdam **ambos** de `bag`, sem cuidado
`searchable_array_bag` teria **duas cópias** de `bag` (ambiguidade, membros
duplicados). A solução usada no repo: herança **virtual**.

```cpp
class array_bag      : virtual public bag { ... };
class searchable_bag : virtual public bag { ... };
class searchable_array_bag : public array_bag, public searchable_bag { ... };
//                              ↑ só uma cópia de bag no fim
```

Regra mental: **quando dois ramos compartilham um ancestral, use `virtual`**
no ponto de herança do ancestral. É o que os headers fornecidos já fazem.

---

## 3. Polimorfismo e *object slicing*

O `main` faz:

```cpp
searchable_bag *t = new searchable_tree_bag;   // ponteiro de base, objeto derivado
t->insert(42);                                 // chama a versão de tree_bag
...
const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
```

- `static_cast<searchable_array_bag&>` rebaixa a referência de volta para o tipo
  concreto — funciona porque `a` **é** de fato um `searchable_array_bag`.
- **Slicing** acontece quando você copia um objeto derivado **por valor** para o
  tipo base: os dados da parte derivada são cortados. Por isso se usa
  ponteiro/referência para polimorfismo.

---

## 4. Orthodox Canonical Form (OCF)

Toda classe do exam precisa de 4 funções:

```cpp
class T
{
public:
    T();                                 // 1. construtor padrão
    T(const T &other);                   // 2. construtor de cópia
    T &operator=(const T &other);        // 3. atribuição de cópia
    ~T();                                // 4. destrutor
};
```

- Regra dos 3: se você escreve um dos três (cópia/atribuição/destrutor), escreva
  os três.
- `operator=` deve tratar **auto-atribuição**:

```cpp
T &T::operator=(const T &other)
{
    if (this != &other)
        /* copiar */
    return (*this);
}
```

- Para classes com **referência** como membro, `operator=` não consegue
  re-seatar a referência (ver `set` no `01-polyset.md`). Isso é uma tensão real
  entre OCF e design; o exam aceita a abordagem do repo.

---

## 5. `const`-correctness

- Métodos que não modificam o objeto → marcar `const`.
- Parâmetro de cópia que não muda → `const T&`.
- Retorno de membro interno que não deve ser alterado → `const searchable_bag&`.

```cpp
bool has(int value) const;              // não modifica a bag
const searchable_bag &get_bag() const;  // devolve referência somente-leitura
```

Se você esquecer o `const` no `has`, o `main` não compila em
`const searchable_array_bag tmp(...); tmp.has(1);`.

---

## 6. `operator[]` duplo (const e não-const)

Para permitir `v[0] = 5;` **e** leitura de objeto `const`:

```cpp
int &operator[](int i);         // versão não-const → mutável
int  operator[](int i) const;   // versão const   → cópia, só leitura
```

O compilador escolhe pela constância do objeto. Usado em `vect2`.

---

## 7. Pré vs pós incremento/decremento

```cpp
T &operator++();    // ++x  → muda e devolve referência
T  operator++(int); // x++  → devolve CÓPIA do valor antigo (parâmetro int "dummy")
```

O `int` no parâmetro não tem nome e é só um desambiguador de assinatura.
Usado em `bigint` e `vect2`.

---

## 8. Memória dinâmica: `delete` vs `delete[]` e deep copy

- `new int` → `delete`  ·  `new int[n]` → `delete[]`.
- Misturar é UB (na prática, com tipos triviais "funciona", mas é erro).
- **Deep copy**: ao copiar uma classe que possui ponteiro, aloque novo buffer e
  copie os dados. Copiar só o ponteiro = *shallow copy* → *double free*.

```cpp
array_bag::array_bag(const array_bag &other)
{
    data = new int[other.size];
    for (int i = 0; i < other.size; i++)
        data[i] = other.data[i];
    size = other.size;
}
```

> Observação do repo: o `array_bag` **fornecido** faz `delete this->data;`
> mesmo sendo `new int[]`. É um bug do material. Como é arquivo do subject,
> **não mexa**; apenas saiba explicar.

---

## Resumo mental por prova

| Conceito | polyset | bigint | vect2 |
|----------|:------:|:------:|:-----:|
| Abstrata / herança múltipla | ✔ | | |
| Herança virtual | ✔ | | |
| Referência como membro | ✔ (`set`) | | |
| OCF | ✔ | ✔ | ✔ |
| `operator[]` duplo | | | ✔ |
| `++`/`--` pré/pós | | ✔ | ✔ |
| `<<` de stream | | ✔ | ✔ |
| Deep copy manual | | (vector) | |
| Aritmética com carry | | ✔ | |
