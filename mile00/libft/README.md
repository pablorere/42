# libft

A from-scratch reimplementation of a subset of the C standard library, plus
utility functions used throughout the 42 curriculum. Produces a static library
`libft.a`.

## Build

```sh
make        # build libft.a
make clean
make fclean
make re
```

## Contents

- **Character checks / conversions** — `ft_isalpha`, `ft_isdigit`, `ft_tolower`, …
- **String functions** — `ft_strlen`, `ft_strjoin`, `ft_split`, `ft_substr`, `ft_strtrim`, …
- **Memory functions** — `ft_memset`, `ft_memmove`, `ft_calloc`, `ft_bzero`, …
- **Output helpers** — `ft_putchar_fd`, `ft_putstr_fd`, `ft_putnbr_fd`, `ft_putendl_fd`

## Usage

```c
#include "libft.h"

ft_putstr_fd("Hello, 42!\n", 1);
```

Link it with `-L. -lft`.
