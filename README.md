# Game of Life

Quick implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with C. 

## Using the code

To run compile the code you just need to run: 

```zsh
make
``` 

Once you have the executable version run it with:

```zsh
./game.exe ${DISTRIBUTION}
```

Here the `${DISTRIBUTION}` parameter needs to be a number between 0 and 1, this distribution gives you the density of "life" inside the two dimensional space in which the game is executed. If you want to change the size of the univers in which the game is executed you can go into `game-of-life.c` and change the value of the `ROWS` and `COLS` constants. You could also change the number of iterations the game makes if you modify the `GENERATIONS` constant, a similar constant is `SPEED` and this is the time it takes for the generation to change in microseconds. Keep in mind that the two dimensional space is printed every time the program iterates, try to keep the terminal to a size that makes this changes seamless.
