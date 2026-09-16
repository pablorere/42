# pipex

Recreates shell pipelines and redirections using low-level Unix primitives:
`pipe`, `fork`, `dup2`, `execve` and `waitpid`. Given an input file, two
commands and an output file, it behaves like:

```sh
< file1 cmd1 | cmd2 > file2
```

## Build

```sh
make        # builds ./pipex
make bonus  # builds ./pipex_bonus
make clean
make fclean
make re
```

## Usage

```sh
./pipex file1 "cmd1" "cmd2" file2
```

Example:

```sh
./pipex input.txt "grep foo" "wc -l" output.txt
```

Commands are resolved through the `PATH` environment variable.

## Implementation notes

- The parent process handles the second command and the output redirection.
- The child handles the first command and reads from the input file.
- File descriptors are closed after `dup2` to avoid leaks into the executed
  programs.
