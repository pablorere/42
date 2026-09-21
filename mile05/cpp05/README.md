# C++ Module 05 — Repetition and Exceptions

A study guide to every concept this module expects you to master.

The module builds a small "bureaucracy" simulation: bureaucrats sign and execute
forms, some forms are abstract, and an intern acts as a form factory. Everything
is held together by **exception handling**, **inheritance**, and **abstract
classes**.

This repository also contains a working reference implementation in `ex00`–`ex03`;
this guide explains *why* every piece is written the way it is.

---

## Quick reference

| Exercise | New classes | Idea |
| --- | --- | --- |
| ex00 | `Bureaucrat` | OCF, `const` name, grade in `[1, 150]`, two custom exceptions |
| ex01 | `Form` | `const` name + grades, `beSigned` / `signForm` |
| ex02 | `AForm` (abstract) + `ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm` | polymorphism, Template Method, `execute` |
| ex03 | `Intern` | factory table; `makeForm` returns an `AForm *` |

**Grade rule:** 1 is the best grade and 150 the worst. "Incrementing" a grade
makes it better, so the number goes **down**.

**Required output strings**

| Where | Output |
| --- | --- |
| `operator<<(Bureaucrat)` | `<name>, bureaucrat grade <grade>.` |
| `Bureaucrat::signForm` | `<bureaucrat> signed <form>` or `<bureaucrat> couldn't sign <form> because <reason>` |
| `Bureaucrat::executeForm` | `<bureaucrat> executed <form>` |
| `Intern::makeForm` | `Intern creates <form>` |

**Build and test any exercise**

```bash
cd exNN && make re && ./bureaucrat
```

**Golden rules that are easy to forget:** compile with
`-Wall -Wextra -Werror -std=c++98`; every class needs the Orthodox Canonical
Form (exception classes are exempt); no functions in headers; every header needs
include guards; no `printf` / `malloc` / `free`; no `using namespace` or `friend`;
no STL containers or `<algorithm>`; every `new` needs a `delete`.

---

## Table of contents

1. [Core concepts](#1-core-concepts)
   - [1.1 Classes, const attributes and initializer lists](#11-classes-const-attributes-and-initializer-lists)
   - [1.2 Orthodox Canonical Form](#12-orthodox-canonical-form)
   - [1.3 Encapsulation and getters](#13-encapsulation-and-getters)
   - [1.4 Exception handling](#14-exception-handling)
   - [1.5 Custom exception classes](#15-custom-exception-classes)
   - [1.6 Operator overloading and operator<<](#16-operator-overloading-and-operator)
   - [1.7 Inheritance, virtual and abstract classes](#17-inheritance-virtual-and-abstract-classes)
   - [1.8 The Template Method pattern](#18-the-template-method-pattern)
   - [1.9 The Factory pattern and the Intern](#19-the-factory-pattern-and-the-intern)
   - [1.10 Randomness in C++98](#110-randomness-in-c98)
   - [1.11 Memory management and leaks](#111-memory-management-and-leaks)
   - [1.12 Header hygiene and include guards](#112-header-hygiene-and-include-guards)
2. [Exercise-by-exercise guide](#2-exercise-by-exercise-guide) — ex00, ex01, ex02, ex03 and a file map
3. [Common pitfalls and peer-evaluation checklist](#3-common-pitfalls-and-peer-evaluation-checklist)
4. [Glossary](#4-glossary)

---

## 1. Core concepts

### 1.1 Classes, const attributes and initializer lists

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

### 1.2 Orthodox Canonical Form

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

### 1.3 Encapsulation and getters

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

### 1.4 Exception handling

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

### 1.5 Custom exception classes

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

### 1.6 Operator overloading and `operator<<`

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

### 1.7 Inheritance, virtual and abstract classes

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

### 1.8 The Template Method pattern

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

### 1.9 The Factory pattern and the Intern

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

### 1.10 Randomness in C++98

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

### 1.11 Memory management and leaks

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

### 1.12 Header hygiene and include guards

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

## 2. Exercise-by-exercise guide

This section is both a requirements list and a **learning path**: for every
exercise you get what to learn, the key idea, a minimal skeleton, the traps, and
where each concept lives in this repository.

Build and run any of them with:

```bash
cd exNN && make re && ./bureaucrat
```

---

### ex00 — Mommy, when I grow up, I want to be a bureaucrat!

**Files:** `Makefile`, `main.cpp`, `Bureaucrat.hpp`, `Bureaucrat.cpp`

**Requirements**
- `Bureaucrat` has a **constant name** and a grade in `[1, 150]`.
- An invalid grade in the constructor throws
  `Bureaucrat::GradeTooHighException` or `Bureaucrat::GradeTooLowException`.
- Getters: `getName()`, `getGrade()`.
- Two functions to increment/decrement; out of range throws the same exceptions.
  Grade 1 is the highest, so incrementing 2 gives 1, and incrementing 1 throws.
- Exceptions catchable with `try` / `catch (std::exception& e)`.
- `operator<<` prints `<name>, bureaucrat grade <grade>.`
- Tests proving that all of it works.

**What you must learn**
1. **Const members need the initializer list.** `const std::string _name` cannot
   be assigned in the constructor body, only initialized *before* it runs.
2. **Initialization follows declaration order**, not the order you write in the
   list. Reordering silently initializes with garbage values.
3. **Throwing from a constructor.** If the body throws, the object is never
   "born": already-initialized members are destroyed correctly, and the
   `catch` block sees the exception as if the object never existed. This is why
   checking the grade *after* the initializer list is safe.
4. **Nested exception classes** are the idiomatic way to name them
   `Bureaucrat::GradeTooHighException`: they are scoped to the enclosing class.
5. **`operator<<` must be a free function.** As a member it would be
   `bureaucrat << cout`, which is wrong.

**Skeleton**

```cpp
class Bureaucrat {
private:
    const std::string _name;
    int _grade;
public:
    Bureaucrat();
    Bureaucrat(const std::string &name, int grade);
    Bureaucrat(const Bureaucrat &other);
    Bureaucrat &operator=(const Bureaucrat &other);
    ~Bureaucrat();

    const std::string &getName() const;
    int getGrade() const;
    void incrementGrade();
    void decrementGrade();

    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b);
```

```cpp
Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name), _grade(grade) {
    if (_grade < 1)
        throw GradeTooHighException();
    if (_grade > 150)
        throw GradeTooLowException();
}

void Bureaucrat::incrementGrade() {
    if (_grade == 1)
        throw GradeTooHighException();
    --_grade;               // 1 is the best grade, so incrementing DECREASES the number
}

void Bureaucrat::decrementGrade() {
    if (_grade == 150)
        throw GradeTooLowException();
    ++_grade;
}
```

**Traps**

- **Grade direction.** Incrementing a grade makes it *better*, so the number
  goes down. Getting this backwards is the single most common mistake.
- **Bounds are inclusive.** 1 and 150 are valid; 0 and 151 throw.
- **A `const` member breaks copy assignment.** You cannot do `_name = other._name`
  in `operator=`. Two accepted answers:
  1. Keep `_name` non-const and copy it (what this repo does) — simple, but the
     subject says the name is *constant*.
  2. Keep `_name` `const` and only copy `_grade` in `operator=` — stricter, the
     name of the target object is then never changed by an assignment.

  Choose one and be able to justify it at the defence.
- **Self-assignment.** `a = a` must not destroy the object; guard with
  `if (this != &other)`, or assign through a temporary.
- **Throw inside a ternary.** This is legal:
  ```cpp
  _grade < 1 ? throw GradeTooHighException() : throw GradeTooLowException();
  ```
  Both branches are throw-expressions of type `void`, so the conditional has
  type `void`. But this is **not** legal:
  ```cpp
  throw _grade < 1 ? GradeTooHighException() : GradeTooLowException();  // ERROR
  ```
  because two sibling exception types have no common type to convert to. When in
  doubt, use two plain `if`s — clearer and impossible to get wrong.

---

### ex01 — Form up, maggots!

**Files:** ex00 files + `Form.hpp`, `Form.cpp`

**Requirements**
- `Form`: **constant name**, `bool` "is signed" (`false` at construction),
  **constant sign grade**, **constant execute grade** — all `private`, not
  `protected`.
- Form grades obey the same `[1, 150]` rules and throw
  `Form::GradeTooHighException` / `Form::GradeTooLowException`.
- Getters for everything + an `operator<<` printing all the form information.
- `beSigned(const Bureaucrat&)`: signs if the bureaucrat's grade is **good
  enough** (numeric value `<=` the sign grade), otherwise throws
  `GradeTooLowException`.
- `Bureaucrat::signForm(Form&)` calls `beSigned()` and prints
  `<bureaucrat> signed <form>` on success, or
  `<bureaucrat> couldn't sign <form> because <reason>` on failure.

**What you must learn**
1. **Composition of classes.** `Form` mentions `Bureaucrat` and vice versa —
   the classic circular dependency. Break it with a **forward declaration**
   (`class Bureaucrat;`) in the header and a normal `#include` in the `.cpp`.
2. **Getters returning `const std::string&`** instead of a copy.
3. **Deciding who reports the error.** `beSigned` *throws*; `signForm` *catches*
   and turns the exception into a human-readable message. Never print an error
   from deep inside the model and never `exit()`.
4. **A `bool` member is not `const`** — it changes when the form is signed, so it
   is the one attribute `operator=` can still copy.

**Key comparison — the grade logic**

```cpp
// in Form::beSigned — a lower number means a better grade,
// so the bureaucrat signs successfully when grade <= sign_grade
void Form::beSigned(const Bureaucrat &b) {
    if (b.getGrade() > _sign_grade)
        throw GradeTooLowException();
    _is_signed = true;
}
```

```cpp
// in Bureaucrat::signForm — exceptions become messages
void Bureaucrat::signForm(Form &form) {
    try {
        form.beSigned(*this);
        std::cout << _name << " signed " << form.getName() << std::endl;
    } catch (std::exception &e) {
        std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
    }
}
```

**Traps**

- **`operator=` cannot touch `_name`, `_sign_grade`, `_execute_grade`** because
  they are `const`. Only `_is_signed` is assignable. Same dilemma as ex00 — pick a
  rule and apply it consistently.
- **Reading a form before signing it**: `execute` does not exist yet in ex01;
  signing only flips the flag.
- **`form.getName()` vs `operator<<`** in the messages: `<form>` is conventionally
  the form's *name*, not the whole printed object.

---

### ex02 — No, you need form 28B, not 28C...

**Files:** `Makefile`, `main.cpp`, `Bureaucrat.*`, `AForm.*`,
`ShrubberyCreationForm.*`, `RobotomyRequestForm.*`, `PresidentialPardonForm.*`

**Requirements**
- `Form` becomes the **abstract** class `AForm`; its attributes stay `private`
  and stay in the base.
- Concrete forms take **only a target**:
  - `ShrubberyCreationForm` — sign 145, exec 137 → writes ASCII trees to
    `<target>_shrubbery` in the working directory.
  - `RobotomyRequestForm` — sign 72, exec 45 → drilling noises, then
    `<target> has been robotomized successfully` 50% of the time, else a failure
    message.
  - `PresidentialPardonForm` — sign 25, exec 5 →
    `<target> has been pardoned by Zaphod Beeblebrox`.
- `execute(const Bureaucrat&) const` validates (signed? grade high enough?) and
  then performs the action.
- `Bureaucrat::executeForm(const AForm&) const` attempts execution and prints
  `<bureaucrat> executed <form>`, or an explicit error.

**What you must learn**
1. **Abstract classes and pure virtual functions.**
   `virtual void executeAction() const = 0;` makes `AForm` impossible to
   instantiate, but you can still hold `AForm *` / `AForm &` pointing at derived
   objects. This is the core of runtime polymorphism.
2. **Virtual destructor.** If anything ever `delete`s through an `AForm*`, the
   base destructor must be `virtual`, otherwise the derived destructor is
   skipped. Declare `virtual ~AForm();`.
3. **The Template Method pattern.** The base owns the *skeleton* (validate, then
   act); the derived class fills in only the varying step:

   ```cpp
   // AForm.hpp
   protected:
       virtual void executeAction() const = 0;

   // AForm.cpp
   void AForm::execute(const Bureaucrat &executor) const {
       if (!_is_signed)
           throw NotSignedException();
       if (executor.getGrade() > _execute_grade)
           throw GradeTooLowException();
       executeAction();       // <- the polymorphic hook
   }
   ```

   Writing the same two `if`s inside three different classes is the "ugly" option
   the subject warns about.
4. **A third exception: `NotSignedException`.** "Not signed" and "grade too low"
   are genuinely different errors.
5. **Each derived class stores its own `_target`**, but all *form* attributes
   (name, signed flag, grades) stay in the base and stay `private`.
6. **File output** (`<fstream>`) and **randomness in C++98** (`<cstdlib>`).

**Derived-class skeleton** (the shape repeats three times)

```cpp
class ShrubberyCreationForm : public AForm {
private:
    const std::string _target;
public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(const std::string &target);
    ShrubberyCreationForm(const ShrubberyCreationForm &other);
    ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
    ~ShrubberyCreationForm();
protected:
    virtual void executeAction() const;
};
```

```cpp
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("shrubbery creation", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
    if (this != &other)
        AForm::operator=(other);   // the base copies what it can
    return (*this);
}
```

```cpp
void ShrubberyCreationForm::executeAction() const {
    std::ofstream file((_target + "_shrubbery").c_str());   // C++98: c_str()
    if (!file.is_open())
        throw std::ios_base::failure("could not open the output file");
    file << "   *\n  ***\n *****\n*******\n   |\n   |\n";
}
```

```cpp
void RobotomyRequestForm::executeAction() const {
    std::cout << "* BZZZZZ... drilling noises *" << std::endl;
    if (std::rand() % 2 == 0)                                   // ~50%
        std::cout << _target << " has been robotomized successfully" << std::endl;
    else
        std::cout << _target << " robotomization failed" << std::endl;
}
```

**Traps**

- **`std::ofstream` takes a C string in C++98**: `(_target + "_shrubbery").c_str()`.
- **Seed the RNG once, in `main`**, never inside `executeAction`, or every call
  repeats the same sequence:
  ```cpp
  std::srand(std::time(NULL));   // <cstdlib> + <ctime>
  ```
  `<random>` does not exist in C++98.
- **The copy constructor must forward to `AForm(other)`.** Forgetting it silently
  default-constructs the base and the form loses its name and grades.
- **Pure virtual ≠ no body.** `AForm::execute` is *not* pure virtual; only
  `executeAction` is. `execute` must be a normal (const) member.
- **`AForm` still needs the OCF** even though it is abstract: a protected or
  public default constructor, copy constructor, `operator=`, and a `virtual`
  destructor. You just cannot instantiate it directly.
- **`getTarget()` is not required by the subject** — the target can stay private
  and only be used inside `executeAction`.

---

### ex03 — At least this beats coffee-making

**Files:** ex02 files + `Intern.hpp`, `Intern.cpp`

**Requirements**
- `Intern` has **no name, no grade, no characteristics** — only `makeForm`.
- `makeForm(name, target)` returns a **newly allocated** `AForm *` whose target is
  the second argument.
- Prints `Intern creates <form>`.
- Unknown name → print an explicit error message.
- **No long `if / else if / else` chain** — use a table / factory design.
- The caller owns the returned pointer and must `delete` it.

**What you must learn**
1. **Function pointers** as a way to store "how to build this object" in data.
2. **The Factory pattern**: a table mapping a string to a creation function,
   instead of branching on the string three times.
3. **Ownership and `delete`.** Returning a raw pointer moves the responsibility
   to the caller. This is where ex03 leaks are born.

**Skeleton**

```cpp
class Intern {
public:
    Intern();
    Intern(const Intern &other);
    Intern &operator=(const Intern &other);
    ~Intern();

    AForm *makeForm(const std::string &name, const std::string &target) const;
};
```

```cpp
static AForm *makeShrubbery(const std::string &target) { return (new ShrubberyCreationForm(target)); }
static AForm *makeRobotomy(const std::string &target)  { return (new RobotomyRequestForm(target)); }
static AForm *makePardon(const std::string &target)    { return (new PresidentialPardonForm(target)); }

typedef AForm *(*t_make)(const std::string &);

struct FormEntry {
    const char *name;
    t_make make;
};

static const FormEntry g_forms[] = {
    { "shrubbery creation",   makeShrubbery },
    { "robotomy request",     makeRobotomy },
    { "presidential pardon",  makePardon }
};

AForm *Intern::makeForm(const std::string &name, const std::string &target) const {
    for (int i = 0; i < 3; ++i) {
        if (name == g_forms[i].name) {
            std::cout << "Intern creates " << name << std::endl;
            return (g_forms[i].make(target));
        }
    }
    std::cout << "Intern cannot create " << name << ": unknown form name" << std::endl;
    return (NULL);
}
```

**Traps**

- **Do not leak.** Every pointer returned by `makeForm` needs a `delete`:
  ```cpp
  AForm *f = intern.makeForm("robotomy request", "Bender");
  if (f) {
      boss.signForm(*f);
      boss.executeForm(*f);
      delete f;
  }
  ```
  `delete` through an `AForm *` is only safe because `~AForm` is `virtual`
  (ex02's lesson, reused here).
- **`Intern` is still a class, so it needs the OCF** — but all four members are
  trivial. Omit the parameter names in the definitions
  (`Intern::Intern(const Intern &) {}`) to avoid `-Wunused-parameter`.
- **Unused-parameter / unused-variable warnings are errors** with `-Werror`.
- **Seeding for `RobotomyRequestForm`** still happens in `main`, not here.
- **A `nullptr` in C++98 does not exist** — use `NULL` or `0`.

---

### What this repository implements

| Exercise | Files | Highlights |
| --- | --- | --- |
| ex00 | `Bureaucrat.{hpp,cpp}`, `main.cpp` | OCF, const name, nested exceptions, `operator<<` |
| ex01 | + `Form.{hpp,cpp}` | forward declaration, `beSigned` / `signForm`, third exception set |
| ex02 | + `AForm.{hpp,cpp}`, `ShrubberyCreationForm.*`, `RobotomyRequestForm.*`, `PresidentialPardonForm.*` | abstract base, virtual destructor, Template Method, `executeForm` |
| ex03 | + `Intern.{hpp,cpp}` | factory table with function pointers, ownership / `delete` |

All four compile with:

```bash
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program
```

and were verified clean under AddressSanitizer + UndefinedBehaviorSanitizer:

```bash
c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address,undefined *.cpp -o /tmp/asan_check && /tmp/asan_check
```

---

## 3. Common pitfalls and peer-evaluation checklist

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

## 4. Glossary

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
3. Re-read your code against the [peer-evaluation checklist](#3-common-pitfalls-and-peer-evaluation-checklist)
   before defending the module.
4. When stuck, reason first, then discuss with a peer — the subject explicitly
   values the learning journey over the answer.
