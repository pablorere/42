# 42 School Portfolio

A collection of projects completed through the **42 School** common core
curriculum, written in **C** and **C++**. Projects are grouped by milestone
(`mile00` … `mile04`); each one is self-contained with its own `README.md`,
`Makefile` and build instructions.

The curriculum is built around a "no frameworks, no hand-holding" philosophy:
reimplementing core standard-library and system functionality from scratch, under
strict coding standards, with peer-reviewed correctness.

---

## Projects

| Milestone | Project | Language | Description |
|-----------|---------|----------|-------------|
| `mile00` | [libft](mile00/libft) | C | Personal C standard library: strings, memory, I/O helpers |
| `mile01` | [ft_printf](mile01/ft_printf) | C | `printf` reimplementation with variadic arguments |
| `mile01` | [get_next_line](mile01/get_next_line) | C | Line-by-line file descriptor reader with static buffers |
| `mile02` | [pipex](mile02/pipex) | C | Unix pipes and redirections modelled with `fork`/`dup2`/`execve` |
| `mile02` | [push_swap](mile02/push_swap) | C | Stack sorting with a minimal set of push/rotate operations |
| `mile02` | [so_long](mile02/so_long) | C | 2D game engine built on MiniLibX with map validation |
| `mile03` | [philosophers](mile03/philosophers) | C | Dining philosophers with POSIX threads and mutexes |
| `mile03` | [minishell](mile03/minishell) | C | A small POSIX shell built on `readline` *(work in progress)* |
| `mile04` | [cpp00](mile04/cpp00) | C++ | C++ Module 00 — classes, member functions, I/O streams |
| `mile04` | [cpp01](mile04/cpp01) | C++ | C++ Module 01 — memory allocation, pointers, references |
| `mile04` | [cpp02](mile04/cpp02) | C++ | C++ Module 02 — ad-hoc polymorphism, operator overloading, OCF |
| `mile04` | [cpp03](mile04/cpp03) | C++ | C++ Module 03 — inheritance, virtual inheritance |
| `mile04` | [cpp04](mile04/cpp04) | C++ | C++ Module 04 — subtype polymorphism, abstract classes, interfaces |
| `mile04` | [cub3d](mile04/cub3d) | C | Ray-casting 3D engine on MLX42 *(group project)* |

---

## Repository layout

```
.
├── mile00/
│   └── libft/            # static library, no dependencies
├── mile01/
│   ├── ft_printf/        # static library
│   └── get_next_line/    # standalone module
├── mile02/
│   ├── pipex/            # executable
│   ├── push_swap/        # executable + bonus checker
│   └── so_long/          # executable (requires MiniLibX)
├── mile03/
│   ├── philosophers/     # executable (requires -lpthread)
│   └── minishell/        # executable (requires -lreadline)
├── mile04/
│   ├── cpp00 … cpp04/    # C++ modules (C++98)
│   └── cub3d/            # git submodule (MLX42 ray-caster)
├── LICENSE
└── README.md
```

Most projects vendor the dependencies they need (for example, `pipex` and
`push_swap` include their own copy of `libft`), so they build independently.

## Cloning

`cub3d` is a git submodule and pulls in its own MLX42 submodule, so clone
recursively:

```sh
git clone --recursive <url>
# or, if already cloned:
git submodule update --init --recursive
```

## Building

Most projects are built with:

```sh
cd <project>
make        # build
make clean  # remove object files
make fclean # remove object files and the binary
make re     # full rebuild
```

Requirements: `gcc`/`cc`, `make`, `ar`, and for the C++ modules a C++ compiler.
Some projects need extra libraries — see their READMEs:

- `mile02/so_long` needs **MiniLibX** and X11 (see its README for setup).
- `mile03/minishell` needs **GNU readline** (`libreadline-dev`).
- `mile03/philosophers` needs **POSIX threads** (`-lpthread`).
- `mile04/cub3d` needs **MLX42**, **GLFW**, OpenGL and X11; build from inside
  `mile04/cub3d` after initializing submodules.

## Notes

These projects follow the 42 coding standard (Norm) and were developed as part of
the 42 Urduliz campus curriculum. Source files keep the original 42 headers for
provenance.

`cub3d` is a **group project** by `ppaula-s` and `jhvalenc`; it lives here as a
submodule pointing at its original repository:
<https://github.com/Jhonjairo03s/42_cub3d>.

## License

Released under the [MIT License](LICENSE).
