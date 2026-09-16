# get_next_line

Reads and returns one line at a time from a file descriptor, using a static
buffer so consecutive calls continue where the previous one stopped. Works with
files, standard input and (with the bonus) multiple descriptors.

## Build

This is a standalone module — compile it together with your program:

```sh
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` can be overridden at compile time:

```sh
cc -D BUFFER_SIZE=1024 ...
```

## Usage

```c
#include "get_next_line.h"

int   fd = open("file.txt", O_RDONLY);
char  *line;

while ((line = get_next_line(fd)) != NULL)
{
    ft_putstr_fd(line, 1);
    free(line);
}
close(fd);
```

Returns the line including its trailing newline, or `NULL` at end of file.
