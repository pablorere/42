# 03 — Prova `vect2`

> Assignment: `vect2`
> Expected files: `vect2.cpp`, `vect2.hpp`

## Enunciado (resumo fiel)

Crie uma classe `vect2` representando um **vetor matemático de dimensão 2** com
`int`s.

- Deve suportar **adição**, **subtração** e **multiplicação por escalar**
  (ex.: `(vect2(2,2) * 2 == vect2(4,4))`).
- `operator[]` acessa as componentes (`0` e `1`), **sem checagem de limites**.
- Imprimível com `<<`, de forma que `std::cout << v;` produza **exatamente** o
  mesmo que `s << "{" << v[0] << ", " << v[1] << "}"`.
- O `main` fornecido tem que funcionar.

## O `main` define TODA a interface

```cpp
vect2 v1;                 // (0,0)          → ctor padrão
vect2 v2(1, 2);           // (1,2)          → ctor (int,int)
const vect2 v3(v2);       // cópia const
vect2 v4 = v2;            // init por cópia
v1[0], v1[1]              // operator[] leitura
v3[1]                     // operator[] const
v4++  ++v4  v4--  --v4    // pré e pós inc/dec
v2 += v3;  v1 -= v2;      // += -=
v2 *= 42;                 // *=  (vect2 * int)
v3 + v3 * 2               // + e * (vect2 * int)
3 * v2                    // int * vect2  → precisa função livre/friend
v1 - v1 + v1              // -
-v2                       // - unário
v1[1] = 12;               // operator[] RETORNA referência mutável
v1 == v3; v1 != v3;       // == !=
```

**Nada de memória dinâmica.** É a prova mais "só operadores" das três.

---

## Esqueleto guiado

1. **Membros** `int x, y;` (privados).
2. **OCF**: `vect2()`, `vect2(int,int)`, cópia, `operator=`, destrutor.
3. **`operator[]` duplo**:
   ```cpp
   int &operator[](int i);       // mutável: v[1] = 12
   int  operator[](int i) const; // leitura de const vect2
   ```
4. **Pré/pós** `++`/`--` — incrementam/decrementam `x` e `y`.
5. **Compostos** `+=`, `-=`, `*=`.
6. **Binários const** `+`, `-`, `*` devolvendo novo `vect2`.
7. **Unário** `-`.
8. **`operator*` com `int` à esquerda**: como `3 * v2` tem `int` do lado
   esquerdo, precisa de **função livre** (friend declarada dentro da classe):
   ```cpp
   vect2 operator*(int s, const vect2 &v);
   ```
9. **`operator==` / `!=`**.
10. **`operator<<`** como função livre/friend.

---

## Ordem de avaliação — por que `v2 += v2 += v3` funciona

`v2 += v2 += v3;` com `v2=(9,18)`, `v3=(1,2)`:
1. inner: `v2 += v3` → `v2 = (10,20)`, devolve `v2&`.
2. outer: `v2 += (v2& que agora é (10,20))` → `(9,18)+(10,20) = (20,40)`.
Por isso `operator+=` **deve** devolver `vect2&` (referência), senão a semântica
muda. Já `operator+`/`-`/`*` devolvem **valor**.

---

## Solução comentada — `vect2.hpp`

```cpp
#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
private:
    int x;
    int y;
public:
    vect2();
    vect2(int x, int y);
    vect2(const vect2 &copy);
    vect2 &operator=(const vect2 &copy);
    ~vect2();

    int &operator[](int i);          // mutável
    int operator[](int i) const;     // somente leitura

    vect2 &operator++();             // ++v
    vect2 operator++(int);           // v++
    vect2 &operator--();             // --v
    vect2 operator--(int);           // v--

    vect2 &operator+=(const vect2 &v);
    vect2 &operator-=(const vect2 &v);
    vect2 &operator*=(int s);

    vect2 operator+(const vect2 &v) const;
    vect2 operator-(const vect2 &v) const;
    vect2 operator*(int s) const;
    vect2 operator-() const;         // unário

    bool operator==(const vect2 &v) const;
    bool operator!=(const vect2 &v) const;
};

vect2 operator*(int s, const vect2 &v);              // int * vect2
std::ostream &operator<<(std::ostream &os, const vect2 &v);

#endif
```

## `vect2.cpp`

```cpp
#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2 &copy) : x(copy.x), y(copy.y) {}

vect2 &vect2::operator=(const vect2 &copy)
{
    if (this != &copy)
    {
        x = copy.x;
        y = copy.y;
    }
    return (*this);
}

vect2::~vect2() {}

int &vect2::operator[](int i)
{
    return (i == 0 ? x : y);
}

int vect2::operator[](int i) const
{
    return (i == 0 ? x : y);
}

vect2 &vect2::operator++() { x++; y++; return (*this); }

vect2 vect2::operator++(int)
{
    vect2 tmp = *this;      // guarda o valor ANTIGO
    x++;
    y++;
    return (tmp);
}

vect2 &vect2::operator--() { x--; y--; return (*this); }

vect2 vect2::operator--(int)
{
    vect2 tmp = *this;
    x--;
    y--;
    return (tmp);
}

vect2 &vect2::operator+=(const vect2 &v) { x += v.x; y += v.y; return (*this); }
vect2 &vect2::operator-=(const vect2 &v) { x -= v.x; y -= v.y; return (*this); }
vect2 &vect2::operator*=(int s)          { x *= s;   y *= s;   return (*this); }

vect2 vect2::operator+(const vect2 &v) const { return (vect2(x + v.x, y + v.y)); }
vect2 vect2::operator-(const vect2 &v) const { return (vect2(x - v.x, y - v.y)); }
vect2 vect2::operator*(int s) const          { return (vect2(x * s, y * s)); }
vect2 vect2::operator-() const               { return (vect2(-x, -y)); }

bool vect2::operator==(const vect2 &v) const { return (x == v.x && y == v.y); }
bool vect2::operator!=(const vect2 &v) const { return (!(*this == v)); }

vect2 operator*(int s, const vect2 &v)
{
    return (vect2(v[0] * s, v[1] * s));   // usa o operator[] const
}

std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
    os << "{" << v[0] << ", " << v[1] << "}";
    return (os);
}
```

---

## Armadilhas

1. **`operator[]` só uma versão**: se declarar apenas `int& operator[]`, o
   `v3[1]` de um `const vect2` **não compila**. Precisa da versão `const`.
2. **`int * vect2`**: `3 * v2` não acha `vect2::operator*(int)` (lado esquerdo é
   `int`). Faça função livre `vect2 operator*(int, const vect2&)`.
3. **`+=` devolvendo valor** em vez de `vect2&` → a cadeia `v2 += v2 += v3`
   dá resultado errado.
4. **Pós-incremento** devolve o valor **antigo**; erro clássico é devolver o novo.
5. **`operator<<` não pode ser membro** (o `ostream` fica à esquerda) → função
   livre/friend.
6. **Formato exato** `{x, y}` com espaço e chaves — qualquer diferença de espaço
   quebra a comparação com o `main`.

## Compilar e validar

```sh
mkdir -p vect2 && cd vect2
# copie o main.cpp do subject + vect2.hpp + vect2.cpp
g++ -Wall -Wextra -Werror -std=c++98 main.cpp vect2.cpp -o vect2
./vect2
```

Saída esperada:

```text
v1: {0, 0}
v1: {0, 0}
v2: {1, 2}
v3: {1, 2}
v4: {1, 2}
{1, 2}
{3, 4}
{3, 4}
{1, 2}
v1: {-84, -168}
v2: {20, 40}
-v2: {-20, -40}
v1[1]: -168
v1[1]: 12
v3[1]: 2
v1 == v3: 0
v1 == v1: 1
v1 != v3: 1
v1 != v1: 0
```

> Note nas 4 linhas de `++`/`--`: `v4++` imprime `{1, 2}` (o **antigo**), então
> `++v4` imprime `{3, 4}`. Os comentários do `main` (`// 2, 3`) se referem ao
> **estado resultante**, não ao que é impresso. Não se confunda.
