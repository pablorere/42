# Philosophers — 42 Project

A simulation of the classic **Dining Philosophers Problem** using POSIX threads and
mutexes.  Every bug described below was found, analysed, and fixed; this document
explains the logic behind each fix.

---

## Table of Contents

1. [Problem Description](#problem-description)
2. [Usage](#usage)
3. [Argument Validation Rules](#argument-validation-rules)
4. [Architecture Overview](#architecture-overview)
5. [Bug Fixes and Logic](#bug-fixes-and-logic)
   - [Fix 1 — `#pragma once` → `#ifndef` include guard](#fix-1--pragma-once--ifndef-include-guard)
   - [Fix 2 — `#include <stdio.h>` removed from header](#fix-2--include-stdioh-removed-from-header)
   - [Fix 3 — `ft_error` wrote to stdout instead of stderr](#fix-3--ft_error-wrote-to-stdout-instead-of-stderr)
   - [Fix 4 — TOCTOU race in `announce_death`](#fix-4--toctou-race-in-announce_death)
   - [Fix 5 — TOCTOU race in death detection](#fix-5--toctou-race-in-death-detection)
   - [Fix 6 — Arbitrary 60 ms minimum-time restriction](#fix-6--arbitrary-60-ms-minimum-time-restriction)
   - [Fix 7 — Redundant `philo_nbr == 0` check](#fix-7--redundant-philo_nbr--0-check)
   - [Fix 8 — Embedded tabs in usage error message](#fix-8--embedded-tabs-in-usage-error-message)
   - [Fix 9 — Dead `sign` variable in `ft_atoi`](#fix-9--dead-sign-variable-in-ft_atoi)
   - [Fix 10 — Test expectations corrected](#fix-10--test-expectations-corrected)
6. [Concurrency Design](#concurrency-design)
7. [Known Borderline Cases](#known-borderline-cases)
8. [Building and Testing](#building-and-testing)

---

## Problem Description

N philosophers sit around a circular table.  Between each pair of adjacent
philosophers lies one fork.  A philosopher needs **both** the fork on their left
and the fork on their right to eat.  If a philosopher does not eat within
`time_to_die` milliseconds since their last meal (or since the start of the
simulation), they die.

The simulation must stop as soon as one philosopher dies **or** all philosophers
have eaten at least `number_of_meals` times (optional argument).

---

## Usage

```
./philo N ttdie tteat ttsleep [n_meals]
```

| Argument   | Description                                                  |
|------------|--------------------------------------------------------------|
| N          | Number of philosophers (positive integer)                    |
| ttdie      | Time in ms a philosopher can go without eating before dying  |
| tteat      | Time in ms a philosopher spends eating                       |
| ttsleep    | Time in ms a philosopher spends sleeping                     |
| n_meals    | Optional — stop simulation when every philosopher ate this many times |

### Examples

```bash
./philo 5 800 200 200          # 5 philosophers, comfortable timing
./philo 5 800 200 200 7        # same but stops after each ate 7 times
./philo 1 800 200 200          # single philosopher — always dies
./philo 4 410 200 200          # 4 philosophers, 10 ms buffer — no death
./philo 4 310 200 100          # impossible timing — philosopher dies
```

---

## Argument Validation Rules

`ft_atoi` accepts **positive integers only** with these constraints:

| Input             | Result                            |
|-------------------|-----------------------------------|
| Positive integer  | Accepted                          |
| Leading zeros     | Accepted (`005` = 5)              |
| Plus-sign prefix  | Accepted (`+5` = 5)               |
| Negative number   | Rejected (returns −1)             |
| Float / decimal   | Rejected (`5.5`, `8e2`)           |
| Non-numeric chars | Rejected (`abc`, `5x`)            |
| Overflow (> INT_MAX) | Rejected                       |
| Zero              | Rejected for all fields           |

All four mandatory arguments must be **strictly positive**.  The optional fifth
argument must also be strictly positive when supplied.  There is **no arbitrary
minimum value**; a time of 1 ms is as valid as 800 ms.

---

## Architecture Overview

```
main.c        — entry point, philosopher thread body, simulation launcher
init.c        — argument parsing, mutex and thread initialisation, cleanup
routine.c     — eat / sleep / think cycle for each philosopher thread
monitor.c     — death detection and all-ate detection (monitor thread)
utils.c       — get_time, ft_usleep, print_status, ft_error, ft_atoi
include/philo.h — shared types, structs, and function prototypes
```

### Mutex inventory

| Mutex         | Protects                                           |
|---------------|----------------------------------------------------|
| `fork_mutex[i]` | Individual fork — held while a philosopher eats  |
| `print_mutex` | Console output ordering                            |
| `end_mutex`   | `simulation_end` flag                              |
| `meal_mutex`  | `last_meal_time` and `meals_eaten` per philosopher |

### Lock ordering

To prevent deadlock, all code that needs more than one mutex acquires them in
this fixed order:

```
print_mutex → end_mutex
```

`meal_mutex` is never held at the same time as `print_mutex` or `end_mutex`.

---

## Bug Fixes and Logic

### Fix 1 — `#pragma once` → `#ifndef` include guard

**File:** `include/philo.h`

**Problem:** `#pragma once` is a compiler extension that norminette v3 flags as
non-standard.  The 42 norm requires the traditional preprocessor include guard.

**Before:**
```c
#pragma once
```

**After:**
```c
#ifndef PHILO_H
# define PHILO_H
/* ... contents ... */
#endif
```

**Logic:** `#ifndef PHILO_H` prevents the header from being processed more than
once per translation unit without relying on any compiler extension.

---

### Fix 2 — `#include <stdio.h>` removed from header

**File:** `include/philo.h` → moved to `monitor.c` and `utils.c`

**Problem:** A header should only include what is needed to declare the types and
prototypes it exposes.  `printf` is an implementation detail of specific `.c`
files, not a type used in the header.  Including `stdio.h` in the header forced
every translation unit to pull it in unnecessarily.

**After:** `#include <stdio.h>` appears only in `monitor.c` and `utils.c`, where
`printf` is actually called.

---

### Fix 3 — `ft_error` wrote to stdout instead of stderr

**File:** `src/utils.c`

**Problem:** Error messages were printed with `printf`, which writes to `stdout`
(file descriptor 1).  Error messages must go to `stderr` (fd 2) so that they can
be distinguished from normal simulation output and are not suppressed when the
caller redirects stdout.

**Before:**
```c
void    ft_error(char *msg)
{
    printf("%s", msg);
    exit(1);
}
```

**After:**
```c
void    ft_error(char *msg)
{
    int len;

    len = 0;
    while (msg[len])
        len++;
    write(2, msg, len);
    exit(1);
}
```

**Logic:** `write(2, ...)` sends directly to file descriptor 2 (stderr) without
any buffering.  A manual length loop is used because `strlen` from `<string.h>`
is not available without an additional include, and this keeps the function
self-contained and norminette-compliant.

---

### Fix 4 — TOCTOU race in `announce_death`

**File:** `src/monitor.c`

**Problem (Time-Of-Check to Time-Of-Use):** The original `announce_death` held
`print_mutex` to print the death message, released it, then acquired `end_mutex`
to set `simulation_end = true`.  Between the two mutex operations, another
philosopher thread could acquire `print_mutex`, check that `simulation_end` is
still `false`, and print a message **after** the death announcement:

```
[monitor]  → lock print_mutex
[monitor]  → printf "X died"
[monitor]  → unlock print_mutex
            ← another thread sneaks in here →
            → lock print_mutex
            → lock end_mutex
            → simulation_end still false!
            → printf "Y is eating"   ← WRONG: printed after death
            → unlock end_mutex
            → unlock print_mutex
[monitor]  → lock end_mutex
[monitor]  → simulation_end = true
[monitor]  → unlock end_mutex
```

**After:**
```c
static void announce_death(t_data *data, int philo_id)
{
    pthread_mutex_lock(&data->print_mutex);
    pthread_mutex_lock(&data->end_mutex);
    if (!data->simulation_end)
    {
        printf("%ld %d died\n",
            get_time() - data->start_time, philo_id);
        data->simulation_end = true;
    }
    pthread_mutex_unlock(&data->end_mutex);
    pthread_mutex_unlock(&data->print_mutex);
}
```

**Logic:** Both mutexes are acquired together before the printf.  The flag is set
inside the same critical section.  Any other thread trying to call `print_status`
(which also acquires `print_mutex` then `end_mutex`) will block until `announce_death`
finishes, and will then see `simulation_end == true` and print nothing.  The extra
`!data->simulation_end` guard prevents a double-death message if two philosophers
happen to be detected as dead in the same monitor loop iteration.

---

### Fix 5 — TOCTOU race in death detection

**File:** `src/monitor.c` → `is_philosopher_dead`

**Problem:** `current_time` was sampled **outside** the `meal_mutex` lock.  A
philosopher could eat (updating `last_meal_time`) between when `current_time` was
sampled and when `last_meal_time` was read under the lock.  The monitor would then
compare a stale timestamp against a fresh meal time and could wrongly declare a
death.

**Before:**
```c
bool check_death(t_data *data)
{
    while (i < data->philo_nbr)
    {
        current_time = get_time();   /* sampled here, OUTSIDE mutex */
        if (is_philosopher_dead(data, i, current_time))
        { ...
```
```c
static bool is_philosopher_dead(t_data *data, int i, long current_time)
{
    pthread_mutex_lock(&data->meal_mutex);
    last_meal = data->philos[i].last_meal_time;
    is_dead = (current_time - last_meal >= data->time_to_die); /* stale time! */
    pthread_mutex_unlock(&data->meal_mutex);
```

**After:**
```c
static bool is_philosopher_dead(t_data *data, int i)
{
    long    last_meal;
    long    current_time;
    bool    is_dead;

    pthread_mutex_lock(&data->meal_mutex);
    current_time = get_time();                          /* sampled INSIDE mutex */
    last_meal = data->philos[i].last_meal_time;
    is_dead = (current_time - last_meal >= data->time_to_die);
    pthread_mutex_unlock(&data->meal_mutex);
    return (is_dead);
}
```

**Logic:** Sampling the clock inside the mutex guarantees that `current_time` and
`last_meal_time` are read atomically with respect to the philosopher thread that
updates `last_meal_time`.  A philosopher cannot eat between the two reads, so the
comparison is always consistent.

---

### Fix 6 — Arbitrary 60 ms minimum-time restriction

**File:** `src/init.c` → `parse_arguments`

**Problem:** The original code rejected any simulation where `time_to_die`,
`time_to_eat`, or `time_to_sleep` was less than 60 ms:

```c
if (data->time_to_die < 60 || data->time_to_eat < 60
    || data->time_to_sleep < 60)
    ft_error("Error: Times must be an int bigger than 59ms \n");
```

The 42 subject places **no lower bound** on time values other than they must be
positive integers.  This restriction incorrectly rejected valid inputs such as
`./philo 5 50 50 50` or `./philo 5 800 10 10`.

**After:** The check is removed entirely.  Any strictly positive integer is
accepted.

---

### Fix 7 — Redundant `philo_nbr == 0` check

**File:** `src/init.c` → `parse_arguments`

**Problem:** The code checked `philo_nbr <= 0` (which already catches 0) and then
immediately checked `philo_nbr == 0` again:

```c
if (data->philo_nbr <= 0 ...)
    ft_error(...);
if (data->philo_nbr == 0)        /* unreachable — already caught above */
    ft_error("Error: philo number must be at least 1");
```

The second check is **dead code**: if `philo_nbr == 0`, the first check already
called `ft_error` and exited.

**After:** The redundant check is removed.

---

### Fix 8 — Embedded tabs in usage error message

**File:** `src/main.c`

**Problem:** The usage message used a C-string line continuation (`\` at the end
of a source line).  The indentation whitespace on the continuation line became
part of the string:

```c
ft_error("Error: Invalid arguments\nUsage: \
            ./philo 5 800 200 200 [5]\n");
/* actual output: "Error: Invalid arguments\nUsage: \t\t\t./philo..." */
```

**After:** Adjacent string literal concatenation is used instead:

```c
ft_error("Error: Invalid arguments\n"
    "Usage: ./philo N ttdie tteat ttsleep [n_meals]\n");
```

**Logic:** The C standard guarantees that adjacent string literals are
concatenated at compile time with no intervening characters, producing a clean
message without embedded tabs.

---

### Fix 9 — Dead `sign` variable in `ft_atoi`

**File:** `src/utils.c` → `ft_atoi`

**Problem:** The function kept a `sign` variable initialised to `1` that was
multiplied at the return (`res * sign`), but `sign` was **never changed** from
`1` (because a `-` prefix caused an early `return (-1)` before `sign` could be
set to `-1`).  The multiplication was therefore always a no-op, constituting dead
code and confusing the reader.

**Before:**
```c
int sign;
sign = 1;
if (*str == '-' || *str == '+')
{
    if (*str == '-')
        return (-1);  /* sign never set to -1 */
    str++;
}
...
return ((int)(res * sign));  /* sign is always 1 here */
```

**After:**
```c
if (*str == '-')
    return (-1);
if (*str == '+')
    str++;
...
return ((int)res);
```

**Logic:** Since the function is used to parse philosopher arguments (all of which
must be positive), negative numbers are always rejected with `−1`.  There is no
need for a sign multiplier; removing it makes the intent clear and eliminates the
dead variable.

---

### Fix 10 — Test expectations corrected

**Files:** `.tests/test_edge_cases.sh`, `.tests/test_mandatory.sh`

Several test cases had incorrect expectations:

| Test | Old expectation | Correct expectation | Reason |
|---|---|---|---|
| `200 800 200 200 2` | Rejected (exit 1) | Accepted (exit 0) | 200 philosophers is valid per the subject |
| `5 59 200 200 2` | Rejected | Accepted (philosophers die) | No 60 ms minimum in subject |
| `005 0800 0200 0200 2` | Rejected | Accepted | Leading zeros represent valid integers |
| `+5 +800 +200 +200 2` | Rejected | Accepted | Plus prefix is handled by `ft_atoi` |
| `1 400 200 200 2` | Rejected | Accepted (dies) | Single philosopher with limit is valid input |
| `4 400 200 200` | No death | Death | Zero-buffer timing guarantees death on any real OS |
| `"" 800 200 200 2` | Rejected | N/A | Shell drops empty strings; replaced with `\x01` test |

A new helper `run_valid_test` was added to `test_edge_cases.sh` to cleanly
distinguish between tests that expect *invalid-input rejection* (exit 1) and tests
that expect *successful simulation* (exit 0 or timeout).

---

## Concurrency Design

### Philosopher thread (`philosopher_routine`)

```
while simulation not ended:
    take left fork  (lock fork_mutex[id-1])
    take right fork (lock fork_mutex[id % N])
    update last_meal_time (lock/unlock meal_mutex)
    print "is eating"
    increment meals_eaten (lock/unlock meal_mutex)
    sleep time_to_eat
    drop both forks
    print "is sleeping"
    sleep time_to_sleep
    print "is thinking"
    [odd-count tables: think for time_to_eat/2 to reduce contention]
```

Even-numbered philosopher IDs are delayed by 1 ms at startup to stagger fork
acquisition and reduce contention between adjacent philosophers.

### Monitor thread (`monitor_routine`)

Polls every 500 µs:
1. Checks every philosopher for death (time since last meal ≥ time_to_die).
2. If all philosophers have eaten enough meals, sets `simulation_end`.

Both checks acquire `meal_mutex` for reading to avoid data races.

### `ft_usleep`

Sleeps in 100 µs increments, checking `simulation_end` on each iteration.  This
ensures a thread wakes promptly when the simulation ends rather than sleeping for
the full duration.

---

## Known Borderline Cases

| Arguments        | Expected behavior             | Why |
|-----------------|-------------------------------|-----|
| `4 410 200 200` | No death                      | 10 ms buffer for fork acquisition |
| `4 400 200 200` | Death (unreliable without buffer) | Cycle time = time_to_die, OS jitter causes death |
| `2 400 200 200` | Death                         | Each philosopher sleeps 200+200 ms before re-eating |
| `1 800 200 200` | Death (always)                | Single philosopher can never grab two forks |

---

## Building and Testing

```bash
# Build
make

# Run mandatory subject tests
bash .tests/test_mandatory.sh

# Run edge-case / error-handling tests
bash .tests/test_edge_cases.sh

# Quick sanity checks
./philo 5 800 200 200          # should run forever, no death
./philo 5 800 200 200 7        # should stop after each philosopher eats 7 times
./philo 1 800 200 200          # should print "died" within 800 ms
./philo abc 800 200 200        # should print error to stderr and exit 1

# Clean
make fclean
```
