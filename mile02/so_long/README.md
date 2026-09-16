# so_long

A small 2D game built on **MiniLibX**. The player must collect every coin on the
map and reach the exit, with the map validated before the game starts.

## Map format (`.ber`)

| Char | Meaning |
|------|---------|
| `1` | wall |
| `0` | floor |
| `P` | player start (exactly one) |
| `C` | collectible |
| `E` | exit (exactly one) |

Maps must be rectangular, fully enclosed by walls, and contain a reachable path
from the player to every collectible and the exit.

## Dependencies

This project needs **MiniLibX** and X11. The library is intentionally *not*
vendored; clone it into `lib/mlx` before building:

```sh
git clone https://github.com/42Paris/minilibx-linux.git lib/mlx
make -C lib/mlx
```

X11 development headers are required (`libx11-dev libxext-dev` on Debian/Ubuntu).

## Build

```sh
make
make clean
make fclean
make re
```

## Usage

```sh
./so_long maps/map1.ber
```

Controls: arrow keys or `WASD` to move, `ESC` to quit. The window closes
automatically once all coins are collected and the player reaches the exit.

## Implementation notes

- Map loading, flood-fill reachability and wall/enclosure validation are split
  into dedicated modules under `src/`.
- Textures are loaded from `textures/` (XPM).
