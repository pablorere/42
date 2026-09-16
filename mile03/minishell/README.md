# minishell

A small POSIX shell built on GNU `readline`: an interactive prompt that
tokenises input, expands commands and executes built-ins or external programs.

> **Status: work in progress.** The current implementation covers the readline
> loop, signal handling and a set of built-ins. Parsing/execution is still being
> completed and the project does not build yet.

## Dependencies

```sh
sudo apt install libreadline-dev
```

## Build

```sh
make
make clean
make fclean
make re
```

## Usage

```sh
./minishell
```

## Structure

```
main.c              # readline loop, command dispatch
srcs/builtins.c     # built-in commands
srcs/signals.c      # SIGINT / SIGQUIT handling
srcs/utils.c        # PATH lookup, string helpers
include/            # headers + vendored libft
```

## Roadmap

- [x] Interactive readline prompt with history
- [x] Signal handling
- [x] Built-ins
- [ ] Tokeniser with quote handling
- [ ] Pipes and redirections
- [ ] Environment expansion
