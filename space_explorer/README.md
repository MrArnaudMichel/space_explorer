# Space Explorer

## Description

Space Explorer is a game where you can explore the universe to find a planet in a minimum amount of hops. The game is based on a graph where each node represents a planet and each edge represents a wormhole. The game is implemented in C and use a backtracking algorithm to find the shortest path between two planets.

## How to run

To run the game, you need to have the GCC compiler installed.

To compile the game, run the following command:
```bash
gcc space_explorer.c space_solution.c -lm -o space_explorer
```

To run the game, run the following command:
```bash
./space_explorer
```