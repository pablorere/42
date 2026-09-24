# 02 — Prova `bigint`

> Assignment: `bigint`
> Expected files: `bigint.hpp`, `bigint.cpp`

## Enunciado (resumo fiel)

Implemente uma classe `bigint` que armazena um inteiro **sem sinal** de
**precisão arbitrária** (maior que `SIZE_MAX`), sem perda de precisão —
normalmente guardando as "partes" do número em array/string.

Deve suportar:

- **adição** (`+`, `+=`, `++` pré/pós),
- **comparação** (`< > <= >= == !=`),
- **digitshift** — como bitshift, mas deslocando **dígitos em base 10**:
  `42 << 3 == 42000` e `1337 >> 2 == 13`,
- impressão com `operator<<` (base 10, **sem zeros à esquerda**).

O `main.cpp` fornecido tem que compilar.

## O `main` define a interface exata

```cpp
const bigint a(42);
bigint b(21), c, d(1337), e(d);
std::cout << ... << a + b ...;
std::cout << ... << (c += a) ...;
++b;  b++;
(b << 10) + 42;
d <<= 4;          // shift com int
d >>= (const bigint)2;   // shift com bigint → precisa overload para bigint!
...
d < a; d > a; d == a; d != a; d <= a; d >= a;
```

Conclusões de interface:

1. `bigint(int)` implícito (não-`explicit`) — `a(42)`, `b(21)`, `d(1337)`, `e(d)`.
2. `bigint()` padrão → **deve valer 0**.
3. `<<`/`>>` e `<<=`/`>>=` precisam de **duas** sobrecargas: uma para `int`
   (`shift`) e outra para `const bigint&`.
4. Todos os operadores de comparação.
5. `operator<<` de stream como função **friend** (ou livre).

---

## Representação escolhida (little-endian)

Guarde os dígitos em `std::vector<int>`, com `digits[0]` sendo as **unidades**:

```text
1337  →  digits = [7, 3, 3, 1]   // invertido
```

Por quê invertido? Porque o carry da soma caminha das unidades para as dezenas,
e `push_back` no fim é O(1). Imprimir é só percorrer do fim para o começo.

**Invariante:** nunca ter zero à esquerda (exceto o próprio 0). O método
`trim()` remove `digits.back() == 0` enquanto `size() > 1`.

---

## Esqueleto guiado

1. **`trim()`**: `while (digits.size() > 1 && digits.back() == 0) pop_back();`
2. **Construtores**:
   - padrão → `digits(1, 0)`.
   - `unsigned long long n` → extrai dígitos com `%10` / `/=10`; se `n==0`,
     empurra um 0.
   - `std::string` → lê de trás para frente, aceita só dígitos; se vazio, 0; `trim`.
3. **`operator+`** (o coração):
   ```text
   carry = 0
   para i de 0 até max(lenA,lenB)-1 (ou enquanto carry):
       soma = carry + A[i] (se existe) + B[i] (se existe)
       resultado[i] = soma % 10
       carry = soma / 10
   trim()
   ```
4. **`operator<<(int shift)`** (digitshift esquerda = multiplicar por 10^shift):
   inserir `shift` zeros **no começo** do vector (índice 0 = unidades). Caso
   especial: 0 continua 0.
5. **`operator>>(int shift)`**: apagar `shift` dígitos do **começo**; se
   `shift >= size`, vira 0; `trim()`.
6. **Comparações**: primeiro por `size()`; se igual, comparar dígito a dígito do
   mais significativo para o menos.
7. **`<<=`/`>>=` com `int`**: reusar `*this = *this << shift`.
   Com `bigint`: converter o shift para `int` (`to_int()`) e delegar.

---

## Solução comentada — `bigint.hpp`

```cpp
#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <vector>

class bigint
{
private:
    std::vector<int> digits;      // little-endian: digits[0] = unidades
    void trim();                  // remove zeros à esquerda
    int to_int() const;           // usado por <<=(const bigint&)
public:
    bigint();
    bigint(unsigned long long n);
    bigint(const std::string &s);
    bigint(const bigint &copy);
    bigint &operator=(const bigint &copy);
    ~bigint();

    friend std::ostream &operator<<(std::ostream &os, const bigint &b);

    bigint &operator++();         // ++b
    bigint operator++(int);       // b++

    bigint operator+(const bigint &b) const;
    bigint &operator+=(const bigint &b);

    bigint operator<<(int shift) const;
    bigint operator<<(const bigint &b) const;
    bigint operator>>(int shift) const;
    bigint operator>>(const bigint &b) const;

    bigint &operator<<=(int shift);
    bigint &operator<<=(const bigint &b);
    bigint &operator>>=(int shift);
    bigint &operator>>=(const bigint &b);

    bool operator<(const bigint &b) const;
    bool operator>(const bigint &b) const;
    bool operator<=(const bigint &b) const;
    bool operator>=(const bigint &b) const;
    bool operator==(const bigint &b) const;
    bool operator!=(const bigint &b) const;
};

#endif
```

## `bigint.cpp`

```cpp
#include "bigint.hpp"
#include <cctype>
#include <algorithm>

void bigint::trim()
{
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}

int bigint::to_int() const
{
    long long res = 0;
    for (int i = (int)digits.size() - 1; i >= 0; i--)
    {
        res = res * 10 + digits[i];
        if (res > 2147483647LL)
            return (2147483647);   // satura (shift normalmente é pequeno)
    }
    return ((int)res);
}

bigint::bigint() : digits(1, 0) {}

bigint::bigint(unsigned long long n)
{
    if (n == 0)
        digits.push_back(0);
    while (n > 0)
    {
        digits.push_back((int)(n % 10));
        n /= 10;
    }
}

bigint::bigint(const std::string &s)
{
    for (int i = (int)s.size() - 1; i >= 0; i--)
        if (std::isdigit((unsigned char)s[i]))
            digits.push_back(s[i] - '0');
    if (digits.empty())
        digits.push_back(0);
    trim();
}

bigint::bigint(const bigint &copy) : digits(copy.digits) {}

bigint &bigint::operator=(const bigint &copy)
{
    if (this != &copy)
        digits = copy.digits;
    return (*this);
}

bigint::~bigint() {}

std::ostream &operator<<(std::ostream &os, const bigint &b)
{
    for (int i = (int)b.digits.size() - 1; i >= 0; i--)
        os << b.digits[i];
    return (os);
}

bigint &bigint::operator++()
{
    *this = *this + bigint(1);
    return (*this);
}

bigint bigint::operator++(int)
{
    bigint tmp = *this;
    ++(*this);
    return (tmp);
}

bigint bigint::operator+(const bigint &b) const
{
    bigint res;
    int carry = 0;
    size_t size = std::max(digits.size(), b.digits.size());

    res.digits.clear();
    for (size_t i = 0; i < size || carry; i++)
    {
        int sum = carry;
        if (i < digits.size())   sum += digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        res.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    res.trim();
    return (res);
}

bigint &bigint::operator+=(const bigint &b)
{
    *this = *this + b;
    return (*this);
}

bigint bigint::operator<<(int shift) const
{
    if (*this == bigint(0))          // 0 deslocado continua 0
        return (bigint(0));
    bigint res = *this;
    res.digits.insert(res.digits.begin(), shift, 0);   // zeros nas unidades
    return (res);                    // 42 << 3 => 42000
}

bigint bigint::operator<<(const bigint &b) const
{
    bigint tmp = *this;
    tmp <<= b;
    return (tmp);
}

bigint bigint::operator>>(int shift) const
{
    bigint res = *this;
    if (shift >= (int)res.digits.size())
        return (bigint(0));
    res.digits.erase(res.digits.begin(), res.digits.begin() + shift);
    res.trim();
    return (res);                    // 1337 >> 2 => 13
}

bigint bigint::operator>>(const bigint &b) const
{
    bigint tmp = *this;
    tmp >>= b;
    return (tmp);
}

bigint &bigint::operator<<=(int shift) { *this = *this << shift; return (*this); }
bigint &bigint::operator<<=(const bigint &b) { *this <<= b.to_int(); return (*this); }
bigint &bigint::operator>>=(int shift) { *this = *this >> shift; return (*this); }
bigint &bigint::operator>>=(const bigint &b) { *this >>= b.to_int(); return (*this); }

bool bigint::operator<(const bigint &b) const
{
    if (digits.size() != b.digits.size())
        return (digits.size() < b.digits.size());
    for (int i = (int)digits.size() - 1; i >= 0; i--)
        if (digits[i] != b.digits[i])
            return (digits[i] < b.digits[i]);
    return (false);
}

bool bigint::operator>(const bigint &b) const
{
    if (digits.size() != b.digits.size())
        return (digits.size() > b.digits.size());
    for (int i = (int)digits.size() - 1; i >= 0; i--)
        if (digits[i] != b.digits[i])
            return (digits[i] > b.digits[i]);
    return (false);
}

bool bigint::operator<=(const bigint &b) const { return (!(*this > b)); }
bool bigint::operator>=(const bigint &b) const { return (!(*this < b)); }

bool bigint::operator==(const bigint &b) const
{
    if (digits.size() != b.digits.size())
        return (false);
    for (size_t i = 0; i < digits.size(); i++)
        if (digits[i] != b.digits[i])
            return (false);
    return (true);
}

bool bigint::operator!=(const bigint &b) const { return (!(*this == b)); }
```

---

## Armadilhas

1. **Shift com `bigint`**: o `main` usa `d >>= (const bigint)2`. Se você só
   sobrecarregar `int`, **não compila**. Precisa das 4 variantes
   `<<`/`>>` × `int`/`bigint` (e `<<=`/`>>=`).
2. **Ordem dos dígitos**: se guardar big-endian, o carry e o `trim` ficam mais
   chatos. Little-endian é mais simples.
3. **Zeros à esquerda**: `13370000 >> 2` precisa virar `133700` e não
   `00133700`. O `trim()` resolve.
4. **0 << shift**: sem o caso especial, você obteria `digits = [0,0,0]` → imprime
   `000`. Trate 0.
5. **Construtor de `unsigned long long` com 0**: sem o `push_back(0)` inicial,
   `digits` fica vazio → imprime vazio.
6. **`isdigit` com `char` negativo** (UTF-8): use `(unsigned char)s[i]`.
7. **Ambiguidade de `int` vs `bigint`** em literais: `bigint(42)` é seguro, mas
   `42 + b` usa o construtor implícito (por isso ele **não** pode ser `explicit`).

## Compilar e validar

```sh
mkdir -p bigint && cd bigint
# copie o main.cpp do subject + bigint.hpp + bigint.cpp
g++ -Wall -Wextra -Werror -std=c++98 main.cpp bigint.cpp -o bigint
./bigint
```

Saída esperada:

```text
a = 42
b = 21
c = 0
d = 1337
e = 1337
a + b = 63
(c += a) = 42
b = 21
++b = 22
b++ = 22
(b << 10) + 42 = 230000000042
(d <<= 4) = 13370000
(d >>= 2) = 133700
a = 42
d = 133700
(d < a) = 0
(d > a) = 1
(d == a) = 0
(d != a) = 1
(d <= a) = 0
(d >= a) = 1
```

> A solução do repo não implementa `-`, `*`, `/`, `%` porque o `main` não usa.
> O README dele menciona essas operações, mas para **passar o exam** basta o que
> o `main` exercita. Não gaste tempo com o que não é chamado.
