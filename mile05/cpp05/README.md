# C++ Module 05 — Repetition and Exceptions

A study guide to every concept this module expects you to master.

The module builds a small "bureaucracy" simulation: bureaucrats sign and execute
forms, forms can be abstract, and an intern acts as a form factory. Everything is
held together by **exception handling**, **inheritance**, and **abstract
classes**.

> This is a learning/reference document, not a solution. Per the subject's AI
> guidance, the goal is to understand the reasoning — write the code yourself.

---

## Table of contents

1. [Overview and constraints](#1-overview-and-constraints)
2. [General rules you must respect](#2-general-rules-you-must-respect)
3. [Core concepts](#3-core-concepts)
   - [3.1 Classes, const attributes and initializer lists](#31-classes-const-attributes-and-initializer-lists)
   - [3.2 Orthodox Canonical Form](#32-orthodox-canonical-form)
   - [3.3 Encapsulation and getters](#33-encapsulation-and-getters)
   - [3.4 Exception handling](#34-exception-handling)
   - [3.5 Custom exception classes](#35-custom-exception-classes)
   - [3.6 Operator overloading and operator<<](#36-operator-overloading-and-operator)
   - [3.7 Inheritance, virtual and abstract classes](#37-inheritance-virtual-and-abstract-classes)
   - [3.8 The Template Method pattern](#38-the-template-method-pattern)
   - [3.9 The Factory pattern and the Intern](#39-the-factory-pattern-and-the-intern)
   - [3.10 Randomness in C++98](#310-randomness-in-c98)
   - [3.11 Memory management and leaks](#311-memory-management-and-leaks)
   - [3.12 Header hygiene and include guards](#312-header-hygiene-and-include-guards)
4. [Exercise-by-exercise requirements](#4-exercise-by-exercise-requirements)
5. [Common pitfalls and peer-evaluation checklist](#5-common-pitfalls-and-peer-evaluation-checklist)
6. [Glossary](#6-glossary)

---

## 1. Overview and constraints

- Language: **C++** compiled with `-Wall -Wextra -Werror`.
- Your code must still compile with **`-std=c++98`**.
- The module is about **Object-Oriented Programming**, not C with classes.
- Exception classes are the one documented exception to the usual design rules:
  they do **not** have to follow the Orthodox Canonical Form. Every other class
  must.

Build example:

```bash
c++ -Wall -Wextra -Werror -std=c++98 main.cpp Bureaucrat.cpp Form.cpp -o program
```

---

## 2. General rules you must respect

**Compiling**
- `c++ -Wall -Wextra -Werror` and also compiles with `-std=c++98`.

**Formatting / naming**
- Directories: `ex00`, `ex01`, ... `exn`.
- Class names in **UpperCamelCase**.
- A class lives in files named after the class:
  `ClassName.hpp` / `ClassName.h`, `ClassName.cpp`, (optionally `ClassName.tpp`).
- Every output message ends with a newline and goes to standard output.
- No Norminette in the C++ modules — but write clean, readable code your peers
  can grade.

**Allowed / forbidden**
- You may use almost all of the standard library, and should prefer C++-ish
  facilities over their C counterparts.
- No external libraries. **C++11 and derived forms and Boost are forbidden.**
- Forbidden functions: `*printf()`, `*alloc()`, `free()`. Using them = grade 0.
- `using namespace <ns_name>` and `friend` are forbidden unless explicitly
  stated = **-42**.
- **STL is only allowed in Modules 08 and 09.** That means no containers
  (`vector`, `list`, `map`, ...) and no algorithms (`<algorithm>`) here = **-42**.

**Design requirements**
- `new` means you must avoid **memory leaks**.
- From Module 02 to Module 09 every class must be in **Orthodox Canonical Form**
  except when explicitly stated otherwise.
- A function implementation placed in a header file (except function templates)
  = **0** for the exercise.
- Each header must be usable **independently** and must include all its
  dependencies; use **include guards** to prevent double inclusion = **0**
  otherwise.

**Makefile**: same rules as in C (see the Norm chapter about the Makefile).

---

## 3. Core concepts

### 3.1 Classes, const attributes and initializer lists

A class groups data (attributes) and behaviour (member functions). Members can
be `private`, `protected`, or `public`; by convention the data members are
`private` and accessed through functions.

A `const` member must be initialized in the **constructor initializer list** —
it cannot be assigned in the body, because assignment would require modifying
it:

```cpp
class Bureaucrat
{
private:
    const std::string _name;
    int               _grade;

public:
    Bureaucrat(const std::string& name, int grade);
};

// Initializer list: order follows the declaration order of the members,
// NOT the order written here.
Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : _name(name), _grade(grade)
{
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
}
```

Key facts to internalize:
- Members are initialized in **declaration order**, regardless of the order in
  the initializer list. Compilers warn about reordering (`-Wreorder`).
- `const` members make the class non-assignable by default (you cannot reassign
  a const member) — this matters for the Orthodox Canonical Form.
- A grade of **1 is the highest** and **150 is the lowest**. "Incrementing" a
  grade means making it *better*, so grade 3 increments to grade 2.

### 3.2 Orthodox Canonical Form

Any class from Module 02 onward must define these four special members:

1. **Default constructor**
2. **Copy constructor**
3. **Copy assignment operator** (`operator=`)
4. **Destructor**

```cpp
class Bureaucrat
{
public:
    Bureaucrat();
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();
};
```

Why all four? Because if the compiler generates some of them for you, it may
generate ones that do the wrong thing (for example, a shallow copy when you own
a resource). Defining them explicitly makes ownership and copying behaviour
obvious.

- The **copy assignment operator** must handle **self-assignment**
  (`a = a`), otherwise you can destroy your own resource.
- The copy assignment has nothing to assign into a `const` member, so a class
  with a `const` member cannot be meaningfully copy-assigned — an important
  detail when you write `Bureaucrat` and `AForm`.
- The subject explicitly exempts **exception classes** from OCF.

### 3.3 Encapsulation and getters

Attributes are `private`; the outside world reads them through getters:

```cpp
const std::string& getName() const;  // return const ref to avoid copies
int                getGrade() const;
```

Rules of thumb:
- Mark getters `const` — they do not modify the object.
- Return `const` references for objects rather than copies where possible.
- `Form`'s attributes are `private`, and per ex02 they must **remain** in the
  base class even after it becomes abstract.

### 3.4 Exception handling

Exceptions separate *error detection* from *error handling*.

```cpp
try
{
    /* do some stuff with bureaucrats */
}
catch (std::exception& e)
{
    /* handle exception */
}
```

- `throw` raises an exception object.
- The stack unwinds: local objects between the `throw` and the matching `catch`
  are destroyed (this is RAII — resource cleanup happens automatically).
- `catch` is matched by type; order matters (specific before general).
- **Catch by reference** (`std::exception& e`), not by value — catching by
  value slices derived objects and copies.
- `std::exception` (from `<exception>`) is the standard base class and provides
  `virtual const char* what() const throw();`.
- You can re-throw the current exception with a bare `throw;`.

The subject's required shape:

```cpp
try
{
    /* do some stuff with bureaucrats */
}
catch (std::exception& e)
{
    /* handle exception */
}
```

### 3.5 Custom exception classes

The module asks for exceptions named like `Bureaucrat::GradeTooHighException`
and `Form::GradeTooLowException`. The natural way is to define them as **nested
classes** that publicly inherit from `std::exception` and override `what()`:

```cpp
class Bureaucrat
{
public:
    class GradeTooHighException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
};

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade is too high";
}
```

Points:
- Inheriting from `std::exception` is what makes them catchable via
  `catch (std::exception& e)` as the subject requires.
- `what()` must be `virtual`, `const`, and (in C++98) use the `throw()`
  exception specification.
- Nested classes are scoped: `Bureaucrat::GradeTooHighException`. Access them
  from member functions as `GradeTooHighException`.
- Exception classes don't need OCF.

### 3.6 Operator overloading and `operator<<`

Operators are functions with special names. The stream insertion operator is
overloaded as a **free function** (a member `operator<<` would put the object on
the left, which is wrong for `std::cout << obj`):

```cpp
std::ostream& operator<<(std::ostream& out, const Bureaucrat& b)
{
    out << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return out;
}
```

- It must return the stream so chaining (`std::cout << a << b`) works.
- The object is taken by `const&`.
- Required output format for `Bureaucrat` (no angle brackets):
  `<name>, bureaucrat grade <grade>.`
- `Form` must also overload `operator<<` to print all its information.

### 3.7 Inheritance, virtual and abstract classes

Inheritance expresses an "is-a" relationship:

```cpp
class AForm { /* base */ };
class ShrubberyCreationForm : public AForm { /* derived */ };
```

- A function is **virtual** when the version called is chosen at runtime based
  on the actual object type (dynamic dispatch / polymorphism).
- A **pure virtual** function has no implementation and makes the class
  **abstract**:

  ```cpp
  virtual void executeAction() const = 0;  // AForm is abstract
  ```

  You cannot instantiate an abstract class, but you can hold a pointer or
  reference to it (`AForm* form = new ShrubberyCreationForm("home");`).
- **Virtual destructor**: if you `delete` through a base pointer, the base
  destructor must be virtual or the derived destructor won't run. For any class
  meant to be a polymorphic base, declare `virtual ~AForm();`.
- ex02 explicitly requires the base `Form` to be renamed `AForm` and be
  abstract, with its attributes still `private` and still owned by the base.

### 3.8 The Template Method pattern

For `execute()`, the subject says either you check requirements in every concrete
class, or you check them once in the base and then call another function to do
the actual work — and that one way is "more elegant".

The elegant way is the **Template Method pattern**:

```cpp
class AForm
{
private:
    void checkExecution(Bureaucrat const& executor) const;  // validation

protected:
    virtual void executeAction() const = 0;  // the concrete step

public:
    void execute(Bureaucrat const& executor) const
    {
        if (!this->isSigned())
            throw NotSignedException();
        if (executor.getGrade() > this->getExecGrade())
            throw GradeTooLowException();
        this->executeAction();  // polymorphic hook
    }
};
```

The base class owns the *skeleton* (validate, then act); derived classes fill in
only the varying step. This avoids duplicating validation in every concrete form
and is a pattern worth naming in the evaluation.

### 3.9 The Factory pattern and the Intern

The intern has **no name, no grade, no unique characteristics** — it only has
`makeForm(name, target)`, which returns a newly allocated `AForm*`:

```cpp
AForm* makeForm(const std::string& name, const std::string& target);
```

The subject forbids "unreadable and messy" solutions such as a long
`if / else if / else` chain. The clean approach is a **factory**: a table mapping
names to creation functions.

In C++98 a compact, readable option is an array of structs holding a name and a
function pointer:

```cpp
struct FormEntry
{
    const char* name;
    AForm* (*make)(const std::string& target);
};

static AForm* makeShrubbery(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}
// ... similar helpers for the other forms

AForm* Intern::makeForm(const std::string& name, const std::string& target)
{
    FormEntry forms[] = {
        { "shrubbery creation", &makeShrubbery },
        { "robotomy request",   &makeRobotomy },
        { "presidential pardon", &makePardon }
    };
    const std::size_t count = sizeof(forms) / sizeof(forms[0]);

    for (std::size_t i = 0; i < count; ++i)
    {
        if (name == forms[i].name)
        {
            std::cout << "Intern creates " << name << std::endl;
            return forms[i].make(target);
        }
    }
    std::cout << "Intern cannot create " << name
              << ": unknown form name" << std::endl;
    return NULL;  // or throw
}
```

Consequences:
- The **caller owns** the returned pointer and must `delete` it (or store it in
  something with RAII). This is a classic source of leaks in ex03.
- Returning `NULL` for an unknown name is one option; the subject only requires
  an "explicit error message", so printing and returning a null pointer is
  acceptable, but you must handle it in your tests.

### 3.10 Randomness in C++98

`RobotomyRequestForm` must succeed **50% of the time** and otherwise report
failure. `<random>` is a C++11 header, so in C++98 use the C standard library
facilities available through `<cstdlib>` / `<ctime>`:

```cpp
#include <cstdlib>
#include <ctime>

std::srand(std::time(NULL));         // seed once (e.g. in main)
bool success = (std::rand() % 2 == 0);
```

- Seed once, not on every call, or you get repeating sequences.
- `std::rand()` gives pseudo-random integers; `% 2` yields 0 or 1.
- The exact distribution doesn't need to be perfect for the module; it needs to
  be plausible and documented.

### 3.11 Memory management and leaks

- Every `new` needs a matching `delete`; every `new[]` a matching `delete[]`.
- If a constructor throws after partially allocating, earlier allocations can
  leak — prefer stack objects or RAII where you can.
- In ex03 the Intern returns raw pointers; testing them means tracking and
  deleting each one.
- Valgrind is your friend during evaluation:

  ```bash
  valgrind --leak-check=full ./program
  ```

- The subject forbids `malloc`/`free` — use `new`/`delete`.

### 3.12 Header hygiene and include guards

- Each header must include everything it needs (e.g. `<string>`,
  `<iostream>`, `<exception>`) so it can be included on its own.
- Prevent double inclusion with guards:

  ```cpp
  #ifndef BUREAUCRAT_HPP
  #  define BUREAUCRAT_HPP
  // ...
  #endif
  ```

- Do **not** put function implementations in headers (except templates) — that's
  a grade of 0.

---

## 4. Exercise-by-exercise requirements

### ex00 — Mommy, when I grow up, I want to be a bureaucrat!

- Directory: `ex00/`
- Files: `Makefile`, `main.cpp`, `Bureaucrat.{h,hpp}`, `Bureaucrat.cpp`
- Forbidden: none

Requirements:
- `Bureaucrat` has a **constant name** and a grade in `[1, 150]`.
- Instantiating with an invalid grade throws
  `Bureaucrat::GradeTooHighException` or `Bureaucrat::GradeTooLowException`.
- Getters: `getName()`, `getGrade()`.
- Two member functions to increment/decrement the grade; out-of-range throws the
  same exceptions as the constructor. Remember: grade 1 is highest — incrementing
  grade 3 gives grade 2, and incrementing grade 1 throws `GradeTooHighException`.
- Exceptions must be catchable with `try` / `catch (std::exception& e)`.
- `operator<<` prints: `<name>, bureaucrat grade <grade>.`
- Submit tests proving it works.

### ex01 — Form up, maggots!

- Directory: `ex01/`
- Files: previous files + `Form.{h,hpp}`, `Form.cpp`
- Forbidden: none

Requirements:
- `Form` has a **constant name**, a **bool** "is signed" (false at construction),
  a **constant sign grade**, and a **constant execute grade**.
- All attributes are `private`, not `protected`.
- Form grades follow the same `[1,150]` rules and throw
  `Form::GradeTooHighException` / `Form::GradeTooLowException`.
- Getters for all attributes and an `operator<<` printing all form info.
- `beSigned(Bureaucrat&)`: signs the form if the bureaucrat's grade is **>=**
  the required sign grade (remember lower number = higher grade); otherwise
  throws `Form::GradeTooLowException`.
- `Bureaucrat::signForm(Form&)` calls `Form::beSigned()`; on success prints
  `<bureaucrat> signed <form>`, otherwise
  `<bureaucrat> couldn't sign <form> because <reason>.`
- Submit tests.

### ex02 — No, you need form 28B, not 28C...

- Directory: `ex02/`
- Files: `Makefile`, `main.cpp`, `Bureaucrat.*`, `AForm.*`,
  `ShrubberyCreationForm.*`, `RobotomyRequestForm.*`, `PresidentialPardonForm.*`
- Forbidden: none

Requirements:
- Base `Form` becomes an **abstract class** renamed `AForm`; attributes stay
  `private` and in the base.
- Concrete forms (each takes only a **target** constructor parameter):
  - `ShrubberyCreationForm` — sign 145, exec 137. Writes ASCII trees to
    `<target>_shrubbery` in the working directory.
  - `RobotomyRequestForm` — sign 72, exec 45. Drilling noises, then reports
    `<target> has been robotomized successfully` 50% of the time, else failure.
  - `PresidentialPardonForm` — sign 25, exec 5. Reports `<target> has been
    pardoned by Zaphod Beeblebrox`.
- `execute(Bureaucrat const& executor) const` in the base form checks that the
  form is signed and the executor's grade is high enough, then performs the
  action. Throwing the appropriate exception otherwise.
- Prefer doing the checks once in the base and delegating to a concrete action
  (Template Method).
- `Bureaucrat::executeForm(AForm const& form) const` attempts execution; on
  success prints `<bureaucrat> executed <form>`, otherwise an explicit error.
- Submit tests.

### ex03 — At least this beats coffee-making

- Directory: `ex03/`
- Files: previous files + `Intern.{h,hpp}`, `Intern.cpp`
- Forbidden: none

Requirements:
- `Intern` has no name/grade/characteristics.
- `makeForm(name, target)` returns an `AForm*` for the matching form, target
  initialized to the second argument.
- Prints `Intern creates <form>`.
- Unknown name: print an explicit error message.
- **No excessive if/else-if/else chain** — use a table/factory design.
- Example from the subject:

  ```cpp
  {
      Intern   someRandomIntern;
      AForm*   rrf;

      rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  }
  ```
- Test everything, and don't leak the returned pointers.

---

## 5. Common pitfalls and peer-evaluation checklist

Grade logic (the #1 source of bugs):
- [ ] Grade 1 is the **highest**; incrementing improves (decreases) the number.
- [ ] Bounds are inclusive: 1 and 150 are valid.
- [ ] Constructor, increment, and decrement all throw on out-of-range.

Exceptions:
- [ ] Custom exceptions inherit `std::exception` and override `what()`.
- [ ] `what()` is `virtual const char* what() const throw()`.
- [ ] Catch by reference, not by value.
- [ ] `signForm` / `executeForm` catch and print a readable reason, not crash.

Design:
- [ ] `AForm` is abstract and has a **virtual destructor**.
- [ ] Form attributes are `private` and live in the base class.
- [ ] `execute` validates in the base and calls a virtual action (Template
      Method), rather than duplicating checks in each concrete form.
- [ ] Intern uses a table/factory, not a long if/else-if chain.
- [ ] All non-exception classes follow Orthodox Canonical Form.
- [ ] `operator<<` returns `std::ostream&` and takes `const&`.

Output:
- [ ] Exact strings match the subject, each ending in a newline.
- [ ] `<name>, bureaucrat grade <grade>.` (with the trailing period).

Build & hygiene:
- [ ] Compiles with `-Wall -Wextra -Werror -std=c++98`.
- [ ] Headers are self-sufficient and guarded.
- [ ] No function implementations in headers.
- [ ] No `printf`, `malloc`, `free`, `using namespace`, `friend`, or STL
      containers/algorithms.

Memory:
- [ ] Every `new` has a matching `delete`; run Valgrind on your tests.
- [ ] Intern callers delete returned `AForm*` objects.

---

## 6. Glossary

| Term | Meaning |
| --- | --- |
| **Orthodox Canonical Form (OCF)** | A class defining default ctor, copy ctor, copy assignment, and destructor. |
| **Initializer list** | Constructor syntax `: _member(value)` that initializes members (required for `const` members). |
| **Encapsulation** | Hiding data behind `private` and exposing it through functions. |
| **Getter** | A `const` member function returning (a reference to) an attribute. |
| **Exception** | An object thrown with `throw` and handled with `catch`. |
| **Stack unwinding** | Destruction of automatic objects between a `throw` and the matching `catch`. |
| **RAII** | Resource Acquisition Is Initialization: resources tied to object lifetime, so unwinding cleans up. |
| **`what()`** | `std::exception` member returning a description; overridden by custom exceptions. |
| **Polymorphism** | Selecting behaviour at runtime through virtual functions. |
| **Pure virtual function** | `= 0`; makes a class abstract. |
| **Abstract class** | A class with at least one pure virtual function; cannot be instantiated. |
| **Virtual destructor** | Ensures the derived destructor runs when deleting through a base pointer. |
| **Template Method pattern** | Base class defines the algorithm skeleton and calls overridable steps. |
| **Factory pattern** | A function/class that creates objects, here mapping form names to constructors. |
| **Memory leak** | Allocated memory that is never freed. |
| **Include guard** | `#ifndef / #define / #endif` preventing a header from being included twice. |
| **STL** | Standard Template Library — containers and algorithms; forbidden until Modules 08–09. |

---

## How to use this guide

1. Read the concept sections in order — each one builds on the last.
2. Implement `ex00` before reading `ex01` requirements in detail, and so on.
3. Re-read your code against the [peer-evaluation checklist](#5-common-pitfalls-and-peer-evaluation-checklist)
   before defending the module.
4. When stuck, reason first, then discuss with a peer — the subject explicitly
   values the learning journey over the answer.
