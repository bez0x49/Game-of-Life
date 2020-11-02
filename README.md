# Game of Life

Implements the *[Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)* cellular automaton proposed by *[John Horton Conway](https://en.wikipedia.org/wiki/John_Horton_Conway)*. The universe of this game is a grid of square cells that could have one of two states: `Dead` or `Alive`. Every cell interacts with its adjacent neighbors, with the following transactions occurring on every step:

- Any live cell with fewer than two live neighbors dies, as if caused by under-population
- Any live cell with two or three live neighbors on to the next generation
- Any live cell with more than three live neighbors dies, as if by overpopulation
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction

The status of the game on each iteration should be displayed to the console, and for convenience, you should pick a reasonable size, such as 20 rows x 50 columns.
