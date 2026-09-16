# push_swap

Sorts a list of integers using two stacks (`a` and `b`) and the smallest possible
number of a restricted set of operations:

- `sa` / `sb` / `ss` — swap the first two elements
- `pa` / `pb` — push the top of one stack onto the other
- `ra` / `rb` / `rr` — rotate a stack upwards
- `rra` / `rrb` / `rrr` — reverse-rotate a stack downwards

## Build

```sh
make        # builds ./push_swap
make bonus  # builds the ./checker bonus
make clean
make fclean
make re
```

## Usage

```sh
./push_swap 4 67 3 87 23
```

The program prints the sequence of operations that sorts the input. Invalid
arguments (non-numeric, duplicates, overflow) print `Error`.

## Implementation notes

- Small sets (2–5 elements) use hand-tuned routines.
- Larger sets use a chunk-based strategy that pushes elements to stack `b` while
  keeping it sorted, then merges back.
- Rotation costs (`rarb`, `rrarrb`, `rarrb`, `rrarb`) are compared to choose the
  cheapest move for each push.

## Bonus — checker

`./checker` reads a list of operations on stdin and reports whether they sort
the given stack (`OK` / `KO`).
