# ft_printf

A reimplementation of C's `printf`, handling variadic arguments with
`stdarg.h`. Produces the static library `libftprintf.a`.

## Supported conversions

| Specifier | Output |
|-----------|--------|
| `%c` | single character |
| `%s` | string |
| `%p` | pointer address in hexadecimal |
| `%d` / `%i` | signed decimal integer |
| `%u` | unsigned decimal integer |
| `%x` / `%X` | hexadecimal (lower / upper case) |
| `%%` | literal `%` |

## Build

```sh
make
make clean
make fclean
make re
```

## Usage

```c
#include "ft_printf.h"

ft_printf("value = %d, name = %s\n", 42, "pablo");
```

Link it with `-L. -lftprintf`.
